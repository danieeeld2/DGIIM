CREAMOS LAS CLAVES Y LAS FIRMAS

openssl genpkey -algorithm RSA -out dani.key.pem

# openssl genpkey -algorithm RSA -out mario.key.pem

# openssl genpkey -algorithm RSA -out javi.key.pem

openssl req -new -x509 -days 1825 -subj "/C=ES/ST=Spain/L=Ab/O=Cd/CN=dani" -key dani.key.pem -out dani.cert.pem

# openssl req -new -x509 -days 1825 -subj "/C=ES/ST=Spain/L=Ab/O=Cd/CN=mario" -key mario.key.pem -out mario.cert.pem

# openssl req -new -x509 -days 1825 -subj "/C=ES/ST=Spain/L=Ab/O=Cd/CN=javi" -key javi.key.pem -out javi.cert.pem

DOS PERSONAS FIRMAN EL PDF Y UNA LO ENCRIPTA Y SE LO PASA A LA TERCERA

openssl smime -sign -in message/gdh.pdf -out message/gdh.pdf.sgn -signer certs/dani.cert.pem -inkey certs/dani.key.pem -binary -nodetach

# openssl smime -resign -in gdh.pdf.sgn -signer mario.cert.pem -inkey mario.key.pem -out gdh.pdf.2.sgn

# openssl smime -encrypt -aes256 -in gdh.pdf.2.sgn -out gdh.pdf.2.sgn.enc javi.cert.pem //SI SE QUIERE ENVIAR A VARIOS BASTA CON ESCRIBIR AQUI LOS CERTIFICADOS DE LAS PERSONAS A LAS QUE SE VA A ENVIAR

UNO DESENCRIPTA, COMPRUEBA LOS CERTIFICADOS Y VERIFICA EL MENSAJE

openssl smime -decrypt -in message/gdh.pdf.2.sgn.enc -out message/gdh2.pdf.sgn -recip certs/dani.cert.pem -inkey certs/dani.key.pem

# openssl smime -decrypt -in gdh.pdf.2.sgn.enc -out gdh2.pdf.sgn -recip javi.cert.pem -inkey javi.key.pem

openssl smime -pk7out -in message/gdh2.pdf.sgn | openssl pkcs7 -print_certs -noout

openssl smime -verify -binary -in message/gdh2.pdf.sgn -noverify -out message/gdh2.pdf
