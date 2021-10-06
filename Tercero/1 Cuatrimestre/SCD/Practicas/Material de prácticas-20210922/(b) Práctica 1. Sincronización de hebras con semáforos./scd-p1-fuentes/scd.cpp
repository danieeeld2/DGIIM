// *****************************************************************************
//
// Semaphores and Hoare monitors implementation using C++11 concurrency features.
// both classes implement FIFO order.
//
// Carlos Ureña Almagro 2017-2021
//
// -----------------------------------------------------------------------------
// Semaphores (class 'Semaphore')
// 
// History:
// April, 2017    : created
// Sept, 15, 2017 : removed reference count, now 'std::shared_ptr' is used instead
// July, 15, 2018 : implemented guaranteed FIFO order
// Oct, 11, 2019  : added move constructor and explicitly deleted copy and
//                  assignement constructors, so no semaphore aliases are created and
//                  'shared_ptr' is no longer needed
// Oct, 25, 2019  : solved a bug in the // LOGM macro (didn't compile in g++)
// May, 2021      : removed use of LOGM macro.
//
//
// -----------------------------------------------------------------------------
// Urgent wait Hoare-like FIFO monitors for C++11
//
// History:
// November 2016 : created
// March 2017    : updated
// Oct-Nov 2017  : using shared_ptr for monitors references
// November 2017 : using guranteed FIFO queues for urgent and monitor queues
// December 2017 : added TODO above, about implementation
// July 2018     : changed implementation to use FIFO semaphores, as described in
//                 Hoare's article.
// Oct 2020      : fixed a bug: 'mutex_count' was not initialized to 0, 
//                 (the bug showed just on mac with the XCode clang compiler, but not in linux
//                  as compiler use to insert initialization to 0 code).
// May 2021      : no longer use semaphores for the queues, use 'FIFOQueue' instead. This guarantees FIFO order
//
//
// References:
//
//  This implementation is based on the design (using semaphores) introduced by Hoare:
//
//  Hoare, C. A. R. (October 1974).
//  "Monitors: an operating system structuring concept".
//  Comm. ACM. 17 (10): 549–557.
//  doi: 10.1145/355620.361161.
//  PDF: https://www.classes.cs.uchicago.edu/archive/2017/fall/33100-1/papers/hoare-monitors.pdf
//
// also described here:
//
// Operating System Concepts, by Abraham Silberschatz, Peter B. Galvin, Greg Gagne
// (and briefly commented here:
//  https://softwareengineering.stackexchange.com/questions/334811/implement-a-monitor-in-terms-of-semaphores
//
// This program uses the "execute around" pattern designed by B.Stroustroup, as described here:
//
//    Wrapping C++ Member Function Calls.
//    Bjarne Stroustrup
//    The C++ Report, June 2000.
//    http://www.stroustrup.com/wrapper.pdf
//
// The code is also inspired in a Java implementation for monitors described here:
//
// Better monitors for Java - By Theodore S. Norvell
// http://www.javaworld.com/article/2077769/core-java/better-monitors-for-java.html
//
// without the need for "enter" or "leave" calls, which are automatically done by
// using the wrapper pattern.
//
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// *****************************************************************************

#include <iostream>
#include <cassert>
#include <thread>  // incluye std::this_thread::get_id()
#include <system_error>
#include "scd.h"

namespace scd
{

//std::mutex mcout ;
using namespace std ;

int num_instances = 0 ;
bool log_semaphores = false ;

using namespace std ;

// ******************************************************************************
// Registering and getting a thread name, useful for debugging.
// -----------------------------------------------------------------------------

// names map, updated in register_thread_name
static std::map< std::thread::id, std::string > names_map ;

// mutex used to access the names map
static std::mutex names_mtx ;

// -----------------------------------------------------------------------------
// register calling thread name in the monitor, useful for debugging

void register_thread_name( const std::string & rol, const int number )
{
  const std::string name = rol + " " + std::to_string(number) ;
  register_thread_name( name );
}

void register_thread_name( const std::string & name )
{
   using namespace std ;
  std::unique_lock<std::mutex> lock( names_mtx );
  // get thread id in ttid
  const thread::id ttid = std::this_thread::get_id() ; // this thread ident.

  // search and abort if already registered
  const auto iter = names_map.find( ttid );
  if ( iter != names_map.end() )
  {
      cout
         << "error in 'register_thread_name': trying to register name '" << name
         <<"' for a thread which was already registered with name '" << iter->second
         << "', aborting"
         << endl ;
      exit(1);
  }

  // insert name
  names_map.insert( std::pair< std::thread::id, std::string>( ttid, name ) );
}

// -----------------------------------------------------------------------------
// get this thread registered name (or "unknown" if not registered)

std::string get_thread_name()
{
  std::unique_lock<std::mutex> lock( names_mtx );

  const auto ttid = std::this_thread::get_id() ; // this thread ident.
  const auto iter = names_map.find( ttid );

  if ( iter != names_map.end() )
    return iter->second ;
  else
    return "(unknown)" ;

}


// *****************************************************************************
// representation of semaphores (not public)

class SemaphoreRepr
{
   friend class Semaphore ;

   public:
   // create with an initial unsigned value
   SemaphoreRepr( unsigned init_value ) ;
   SemaphoreRepr( unsigned init_value, const std::string & p_name );
   ~SemaphoreRepr() ;

   private:

   unsigned
      value ,     // current semaphore value
      num_wt ;    // current number of waiting threads
   std::mutex *
      mtx ;       // for mutual exclusion in semaphore updating
   std::deque<condition_variable *>
      cvs_queue ; // FIFO queue with condition_variables
   std::string
      name ;      // name of the semaphore (can used for debugging)

   void     sem_wait();             // wait operation
   bool     sem_signal();           // signal operation (returns true if there was any waiting thread)

} ;


// *****************************************************************************
// implementation of 'Semaphore' interface

Semaphore::Semaphore( unsigned init_value )
{
   // LOGM( "begins Semaphore::Semaphore( int == " << init_value << ")" );

   assert( repr == nullptr );
   repr = new SemaphoreRepr( init_value );
   assert( repr != nullptr );

   // LOGM( "ends" );
}
// -----------------------------------------------------------------------------

Semaphore::Semaphore( unsigned init_value, const std::string & p_name )
{
   // LOGM( "begins Semaphore::Semaphore( int == " << init_value << ")" );

   assert( repr == nullptr );
   repr = new SemaphoreRepr( init_value, p_name );
   assert( repr != nullptr );

   // LOGM( "ends" );
}
// -----------------------------------------------------------------------------

Semaphore::Semaphore( Semaphore && sem )
{
  // LOGM( "begins Semaphore::Semaphore( Semaphore && sem )" );

  assert( sem.repr != nullptr );
  // LOGM( "     sem.value == " << sem.repr->value << ", sem.num_wt == " << sem.repr->num_wt );

  // move the pointer to this object
  repr = sem.repr ;
  // void the other object
  sem.repr = nullptr ;

  // LOGM( "ends" );
}

// -----------------------------------------------------------------------------

Semaphore::~Semaphore()
{
   // LOGM( "begins Semaphore::~Semaphore(), repr == " << repr );

   if ( repr != nullptr )
      delete repr ;

   repr = nullptr ; // useful at all ????
   // LOGM( "ends"  );
}
// -----------------------------------------------------------------------------

void Semaphore::sem_wait(  )
{
   assert( repr != nullptr );
   repr->sem_wait();
}
// -----------------------------------------------------------------------------

void Semaphore::sem_signal(  )
{
   assert( repr != nullptr );
   repr->sem_signal() ;
}

// -----------------------------------------------------------------------------
// Private access method, just used for debugging

int Semaphore::get_value()
{
   return repr != nullptr ? repr->value : -1 ;
}

// *****************************************************************************
// Implementation of (private) semaphore representation methods

SemaphoreRepr::SemaphoreRepr( unsigned init_value )
{
  // LOGM( "begins SemaphoreRepr::SemaphoreRepr( int == " << init_value << ")" );

  mtx    = new std::mutex ;
  value  = init_value ;
  name   = "(semaphore's name not given)" ;
  num_wt = 0 ;

  num_instances ++  ;
  // LOGM( "ends" );
}
// -----------------------------------------------------------------------------

SemaphoreRepr::SemaphoreRepr( unsigned init_value, const std::string & p_name )
{
  // LOGM( "begins  SemaphoreRepr::SemaphoreRepr( int == " << init_value << ", name = " << p_name << ")" );

  mtx    = new std::mutex ;
  value  = init_value ;
  name   = p_name ;
  num_wt = 0 ;

  num_instances++ ;
  // LOGM( "ends" );
}

// -----------------------------------------------------------------------------

void SemaphoreRepr::sem_wait()
{
   assert( mtx != nullptr );

   // gain mutex
   std::unique_lock<std::mutex> lock( *mtx );

   // check queue size is coherent with the registered number of waiting threads
   assert( cvs_queue.size() == num_wt );

   if ( value == 0 )      // if the current value is 0, we must wait
   {
      // register new waiting thread
      num_wt += 1 ;

      // create and insert new cond. var. at the end (back) of cond. vars. queue
      condition_variable * cv_ptr = new condition_variable ;
      assert( cv_ptr != nullptr );
      cvs_queue.push_back( cv_ptr );

      // wait until signaled and value > 0
      while ( value == 0 )
         cv_ptr->wait( lock ); // release mutex when waiting, re-gain after

      // as this thread was waiting in the beginning (front) node, remove that node and free cv. memory
      assert( cvs_queue.size() == num_wt ) ; assert( cv_ptr != nullptr ) ;
      cv_ptr = cvs_queue.front();
      cvs_queue.pop_front();
      delete cv_ptr;

      // register the thread is no longer waiting
      num_wt -= 1 ;
   }

   // decrease value
   assert( 0 < value );
   value -= 1 ;

   // release mutex (implicit)
}
// -----------------------------------------------------------------------------

bool SemaphoreRepr::sem_signal()
{
  assert( mtx != nullptr );

  // gain mutex
  std::unique_lock<std::mutex> lock( *mtx );

  // check queue size is coherent with the registered number of waiting threads
  assert( cvs_queue.size() == num_wt );

  // increase value
  value += 1 ;

  // signal one waiting thread, if any
  if ( 0 < num_wt )
  {
      assert( cvs_queue.size() > 0 ); // cond. vars. queue must be non-empty
      condition_variable * cv_ptr = cvs_queue.front() ; // get cond.var. at the first queue node
      assert( cv_ptr != nullptr );
      cv_ptr->notify_one() ; // wake up the thread waiting in that cond.var.
                             // that thread will release memory used by the cond.var. and remove the front node
      return true ;
  }
  return false ;

}
// -----------------------------------------------------------------------------

SemaphoreRepr::~SemaphoreRepr()
{
  using namespace std ;
  //cout << "begins ~SemaphoreRepr( value == " << value << ") ...." << endl << flush ;
  assert( mtx != nullptr );

  delete mtx ;
  mtx = nullptr ;
  num_instances -- ;
  //cout << "ends" << endl ;
}

// *****************************************************************************
// Class: FIFOQueue
// Similar to std::condition_variable, but with guraranteed FIFO order 
// ----------------------------------------------------------------------------

class FIFOQueue
{
   public:
   
   FIFOQueue(  ) {} ;
   ~FIFOQueue() ;

   void     wait( std::unique_lock<std::mutex> & guard ); // wait operation
   void     signal();                                     // signal operation 
   unsigned get_nwt();                                    // returns num. of waiting threads

   private:

   unsigned                              num_wt = 0;    // current number of waiting threads
   std::deque<std::condition_variable *> cvs_queue ; // FIFO queue with condition_variables
   //std::string  name ;                             // name of the semaphore (can used for debugging)
} ;


// -----------------------------------------------------------------------------
// wait on the queue, the caller thread must hold the lock referenced by 'guard' 

void FIFOQueue::wait( std::unique_lock<std::mutex> & guard )
{
   // check queue size is coherent with the registered number of waiting threads
   assert( cvs_queue.size() == num_wt );

   // register new waiting thread
   num_wt += 1 ;

   // create and insert new cond. var. at the end (back) of cond. vars. queue
   std::condition_variable * cv_ptr = new std::condition_variable ;
   assert( cv_ptr != nullptr );
   cvs_queue.push_back( cv_ptr );

   // wait until signaled 
   cv_ptr->wait( guard ); // release mutex when waiting, re-gain after

   // as this thread was waiting in the beginning (front) node, remove that node and free cv. memory
   assert( cvs_queue.size() == num_wt ) ; assert( cv_ptr != nullptr ) ;
   cv_ptr = cvs_queue.front();
   cvs_queue.pop_front();
   delete cv_ptr;

   // register the thread is no longer waiting
   num_wt -= 1 ;

}
// -----------------------------------------------------------------------------
// unblock a thread in the queue. The caller thread must own the lock used

void FIFOQueue::signal()
{
   // check queue size is coherent with the registered number of waiting threads
   assert( cvs_queue.size() == num_wt );

   // if there are no threads, do nothing
   if ( 0 == num_wt )
      return 

   assert( cvs_queue.size() > 0 ); // cond. vars. queue must be non-empty
   std::condition_variable * cv_ptr = cvs_queue.front() ; // get cond.var. at the first queue node
   assert( cv_ptr != nullptr );
   cv_ptr->notify_one() ; // wake up the thread waiting in that cond.var.

   // that thread will release memory used by the cond.var. and remove the front node
   // (then it will wait to regain the mutex it used to enter the queue)
}
// -----------------------------------------------------------------------------
// returns the number of waiting threads 

unsigned FIFOQueue::get_nwt()
{
   return num_wt ;
}
// -----------------------------------------------------------------------------

FIFOQueue::~FIFOQueue()
{
  using namespace std ;
  cout << "~FIFOQueue(): num waiting threads == " << num_wt << endl << flush ;
}



// *****************************************************************************
//
// Class: CondVar
// condition variables for Hoare monitors, with guaranteed FIFO order 
// (uses 'FIFOQueue' class)
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//  create an usable condition variable

CondVar::CondVar( HoareMonitor * p_monitor )
{
   monitor = p_monitor ;
   queue = new FIFOQueue() ;

   assert( queue != nullptr );
   assert( monitor != nullptr );
}
// -----------------------------------------------------------------------------
static const char * const msg =
"error: intento de usar una variable condición que no está inicializada con la función 'newCondVar()' en su declaración en el monitor." ;
// "error: trying to use a condition variable which is not properly initialized with 'newCondVar()' function" ;

void CondVar::check( )
{
   if ( monitor == nullptr )
   {
      cout << msg << endl ;
      exit(1);
   }
   assert( monitor->is_running );
   assert( std::this_thread::get_id() == monitor->running_thread_id ); // check this thread is the running thread
   assert( queue != nullptr );
}
// -----------------------------------------------------------------------------
// unconditionally wait on the underlying thread queue

void CondVar::wait()
{   
   using namespace std ;
   check();

   unique_lock<mutex> guard( monitor->access_mutex ); // wait for any operation to complete (gain ME)
   
   if ( monitor->urgent_queue->get_nwt() > 0 )
      monitor->urgent_queue->signal() ; // free one thread in urgent queu, it waits for ME
   else if ( monitor->monitor_queue->get_nwt() > 0 )
      monitor->monitor_queue->signal() ; // free one thread in monitor queu, it waits for ME
   else 
      monitor->is_running = false ; // no one wants to enter, the monitor is going to be freed

   queue->wait( guard );   // free ME + blocked wait + regain ME
   assert( monitor->is_running ); // the thread has been woked up by the running thread, so the monitor must be already running
   monitor->running_thread_id = std::this_thread::get_id() ; // this is the running thread again
   
   // free ME (implicit)
}                                                      

// -----------------------------------------------------------------------------
// signal operation, with "urgent wait" semantics

void CondVar::signal()
{
   using namespace std ;
   check();

   unique_lock<mutex> guard( monitor->access_mutex ); // wait for any operation to complete (gain ME)
   
   if ( queue->get_nwt() == 0 )  // if the queue is empty
      return ;                   //   free ME and return

   queue->signal() ;  // wake up the older thread in the queue (it must wait for ME)
   monitor->urgent_queue->wait( guard ) ; // enter urgent queue: free ME +  blocked wait + gain ME
   assert( monitor->is_running ); // the thread has been woked up by the running thread, so the monitor must be already running
   monitor->running_thread_id = std::this_thread::get_id() ; // this is the running thread again
   // free ME (implicit)
}
// -----------------------------------------------------------------------------
// returns number of threads waiting in the cond.var.

unsigned CondVar::get_nwt()
{
   check();
   return queue->get_nwt( );
}

// *****************************************************************************
// Class: HoareMonitor
//
// -----------------------------------------------------------------------------

HoareMonitor::HoareMonitor()
{
   name = "unknown" ;
   monitor_queue = new FIFOQueue() ;
   urgent_queue  = new FIFOQueue() ;
}
// -----------------------------------------------------------------------------

HoareMonitor::HoareMonitor( const std::string & p_name )
{
   name = p_name ;
   monitor_queue = new FIFOQueue() ;
   urgent_queue  = new FIFOQueue() ;
}
// -----------------------------------------------------------------------------
HoareMonitor::~HoareMonitor()
{
   assert( ! is_running );
}
// -----------------------------------------------------------------------------

CondVar HoareMonitor::newCondVar()
{
   return CondVar( this );  // built and return cond.var.
}

// -----------------------------------------------------------------------------
// enter the monitor, waiting if neccesary

void HoareMonitor::enter()
{
   using namespace std ;
   unique_lock<mutex> guard( access_mutex ); // wait for any operation to complete (gain ME)

   if ( is_running )
      monitor_queue->wait( guard ); // free ME + blocked wait + gain ME
   else 
      is_running = true ;

   running_thread_id = std::this_thread::get_id();
   assert( is_running );
   // free ME (implicit)
}
// -----------------------------------------------------------------------------
// end running monitor code

void HoareMonitor::leave()
{
   // check this is the thread running in the monitor
   assert( is_running );
   assert( std::this_thread::get_id() == running_thread_id );

   unique_lock<mutex> guard( access_mutex ); // wait for any operation to complete (gain ME)
   
   if ( urgent_queue->get_nwt() > 0 )
      urgent_queue->signal() ; // free one thread in urgent queu, it waits for ME
   else if ( monitor_queue->get_nwt() > 0 )
      monitor_queue->signal() ; // free one thread in monitor queu, it waits for ME
   else 
      is_running = false ; // no one wants to enter, the monitor is going to be freed

   // free ME (implicit)
}




// *****************************************************************************


} //  fin namespace HoareMonitors
