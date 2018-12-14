
// ************************** ARCHIVO DONDE SE IMPLEMENTA EL SERVIDOR WEB **************************


// Se implementan las siguientes librerias:
#include "json.hpp"
#include<fstream>
#include "YASL.h"     
#include "checkArgs.h"
#include <iostream>  
#include <cstdlib>     


/* Se especifica el tamaño del buffer; (buffer: Memoria de almacenamiento temporal de información que permite transferir 
los datos entre unidades funcionales con características de transferencia diferentes). */
const uint32_t RCVBUFSIZE = 32;    

// Para usar el archivo config.json se necesita:
using json = nlohmann::json;

// Funcion para la coneccion con el cliente TCP:
void HandleTCPClient(TCPSocket *sock) {
	std::cout << "Handling client ";
	try {
		std::cout << sock->getForeignAddress() << ":";
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign address" << std::endl;
	}
	try {
		std::cout << sock->getForeignPort();
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign port" << std::endl;
	}
	std::cout << std::endl;

	// Send received string and receive again until the end of transmission
	char echoBuffer[RCVBUFSIZE];
	uint32_t recvMsgSize;
	/*while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means
	                                                 // end of transmission
		// Echo message back to client
		sock->send(echoBuffer, recvMsgSize);
	} */
	
	delete sock;

// Se crean las siguientes variables:
::std:string RespuestaHTTP;
::std:string pagina;
::ifstream paginaHTML;


// Para la pagina 1 : INTERNETWORKING.HTML :
 if((pagina == "/INTERNETWORKING.HTML") ){
			root_dir = root_dir + pagina;
			paginaHTML.open(root_dir);
			RespuestaHTTP= "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"; 
		}
 

// Para la pagina 2 :IP I.HTML :
if else(pagina == "/IP.HTML"){
          root_dir = root_dir + pagina;
			paginaHTML.open(root_dir);
			RespuestaHTTP= "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
}


// Para la pagina 3 : NODOS.HTML :
if else(pagina == "/NODOS.HTML"){

   root_dir = root_dir + pagina;
			paginaHTML.open(root_dir);
			RespuestaHTTP= "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
}


// En caso de que no se logre encontrar las paginas solicitadas por el cliente, enviarle el ERROR 404 : 
 		else{
			notFoundFile = notFoundFile + "/404.HTML";
			paginaHTML.open(notFoundFile);
			HTTPResponse= "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"; //status line + header response

		}
	
}

// Funcion principal main:
int main(int argc, char *argv[]) {


//Variables del archivo config.json (ip, puerto, paginas web, mensaje de error).
	uint16_t puerto_servidor;	
	std::string direccion_ip;	
	std::string root_dir;
	std::string notFoundFile;


// Uso del archivo config.json y obtencion de los datos en su interior:
	std::ifstream jsonArchivo;
	jsonArchivo.open("../bin/config.json");	


// Si funciona correctamente, se le deben enviar al cliente las paginas web que esta solicitando:
	if (jsonArchivo.is_open()){
		json configJson;	
		jsonFile >> configJson;	


		direccion_ip = configJson.at("ip");
		puerto_servidor = configJson.at("puerto");
		root_dir = configJson.at("root_dir");
		notFoundFile = configJson.at("notFoundFile");


// En caso contrario, debe enviarle al cliente un mensaje de error:
	}else{
		std::cout << "ERROR 404 \n"; 
	}


// Aqui ocurre la coneccion TCP con el cliente:
	try {
		TCPServerSocket servSock(echoServPort);    

		for (;;) {   
			HandleTCPClient(servSock.accept());    
		}
	} catch (SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	// NOT REACHED

	return EXIT_SUCCESS;
}
