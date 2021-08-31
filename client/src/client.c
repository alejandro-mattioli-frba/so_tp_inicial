#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Hola! Soy un log");
	config = iniciar_config();

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor
	//Loggear valor de config

	if((config_has_property(config,"IP"))){
		ip = config_get_string_value(config, "IP");
		log_info(logger, "archivo config IP: %s\n", ip);
	}

	if((config_has_property(config,"IP"))){
		puerto = config_get_string_value(config, "PUERTO");
		log_info(logger, "archivo config PUERTO: %s\n", puerto);
	}

	if((config_has_property(config,"CLAVE"))){
		valor = config_get_string_value(config, "CLAVE");
		log_info(logger, "archivo config CLAVE: %s\n", valor);
	}

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor
	enviar_mensaje(valor,conexion);
	paquete(conexion);

	free(ip);
	free(valor);
	free(puerto);
	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("tp0.log","TP0",1,LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config= config_create("tp0.config");
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	log_info(logger,"Inicio leer_consola\n");

	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	while(strcmp(leido,"")!= 0){
	// Acá la idea es que imprimas por el log lo que recibis de la consola.
		log_info(logger,"%s",leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);

	log_info(logger,"finalizo leer_consola\n");

}

void paquete(int conexion)
{
	printf("inicio funcion paquete\n");

	//Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();

	leido = readline(">");
	while(strcmp(leido,"")!= 0){
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
		leido = readline(">");
	}
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);
	printf("fin funcion paquete\n");
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
	printf("FIN\n");
}
