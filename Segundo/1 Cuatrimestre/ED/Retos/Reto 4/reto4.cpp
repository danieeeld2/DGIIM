/**
 * @author Daniel Alconchel Vázquez
 */
#include<iostream>
#include<ostream>
#include<vector>
using namespace std;

bool aux=true;	// variable auxiliar global

/**
 * @brief T.D.A. TreeNode
 * Rwpresenta el árbol
 */
struct TreeNode{
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : value(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : value(x), left(left), right(right){}
};

/**
 * @class Solution
 * @brief Se encarga de calcular la solución
 */
class Solution{
	public:
		/**
		 * @brief Función que devuelve la solución
		 * @param S string con el preorder
		 * @return Devuelve el árbol ordenado según su jerarquía
		 */
		TreeNode* recoverFromPreorder(string S){
			int in=0,level=0;
        		return util(in,S,level);
		}
	private:
		/**
		 * @brief Función encargada de generar la solución
		 * @param in 
		 * @param s string con el preorden
		 * @param level
		 * return Devuelve el árbol según su jerarquía
		 */
		TreeNode* util(int &in, string s, int level){
			if(in >= s.length())
				return NULL;
			
			int count =0;
			while(s[in+count] == '-')
				count ++;

			if(count == level){
				in += count;

				long int val=0;
				while(isdigit(s[in])){	// Checkea si el valor es decimal
					val = 10*val +(s[in]-'0');
					in++;
				}

				TreeNode *node = new TreeNode(val);
				node->left  = util(in,s,level+1);
				node->right = util(in,s,level+1);
				return node;
			}
			return NULL;
		}

};

void printGivenLevel(TreeNode* root, int level, ostream& os){
	if(root == NULL && aux){
		os << "null" << " ";
		aux = false;
	}else if(root == NULL && !aux){
		return;
	}else{
		if(level == 1){
			os << root->value << " ";
			aux = true;
		}
		else if(level > 1){
			printGivenLevel(root->left, level-1, os);
			printGivenLevel(root->right, level-1, os);
		}
	}
}

int depth(string S){
	int d=0;
	int max=0; 
	for(int i=0; i<S.size(); i++){
		if(S[i] == '-'){
			d++;
			if(d>max)
				max = d;
		}else{
			d = 0;
		}
	}
	return max;
}

void imprime(ostream&os, TreeNode* root, int alt){
	int h = alt;
	int i;
	for(i=1; i<=h+1; i++){
		printGivenLevel(root,i,cout);
	}
}

int main(){
	string S("1-401--349---90--88");
	Solution solucion;
	imprime(cout, solucion.recoverFromPreorder(S), depth(S));
	cout << endl;
	return 0;
}

