# Firmamos el mensaje y con nodetach creamos un pdf con la firma debe estar incorporada en el archivo de salida en lugar de adjuntarse por separado. 


openssl smime -sign -in message/gdh.pdf -out gdh.pdf.sgn -signer claves/eve.cert.pem -inkey claves/eve.key.pem -binary -nodetach

openssl smime -resign -in gdh.pdf.sgn -signer claves/alice.cert.pem -inkey claves/alice.key.pem -out gdh.pdf.2.sgn 


openssl smime -encrypt -aes256 -in gdh.pdf.2.sgn -out gdh.pdf.2.sgn.enc claves/bob.cert.pem

openssl smime -decrypt -in gdh.pdf.2.sgn.enc -out ../gdh.pdf.2.sgn -inkey claves/bob.key.pem -binary

openssl smime -pk7out -in ../gdh.pdf.2.sgn | openssl pkcs7 -print_certs -noout 
subject=CN = eve@example.com

issuer=C = GB, ST = England, O = Alice Ltd, CN = Alice


subject=CN = alice@example.com

issuer=C = GB, ST = England, O = Alice Ltd, CN = Alice


openssl smime -verify -binary -in ../gdh.pdf.2.sgn -noverify -out ../gdh.pdf 
Verification successful

