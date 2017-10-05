//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor wifi
 *
 * @brief Wifi functions
 *
 * @file
 *
 * You can add a Wifi module into your POB Robotics Suite robot.
 * This module allows you to connect on a wireless network.
 *
 * You can create 2 servers on the robot and 2 remote connection.
 *
 *
 * @par Join a wifi network.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8   result;
    UInt8   buffer[32];
    UInt32  size;
    WifiConnectionInfo infoConnection;


    // Init cpu and robot :
    InitCpu();
    InitRobot();

    ﻿if( InitWifiHardware() == WIFI_OK)
    {
        // Wifi hardware is initialized, now connect to a wifi network:
        if( JoinWifiNetwork( "MyWifiNetwork",13,"mykey",5,0)==WIFI_OK)
        {
            // Now wifi is connected on the 'MyWifiNetwork', configure ip address by te dhcp server :
            if( SetIpConfiguration(1,0,0,0) == WIFI_OK)
            {
                // Create a simple server on TCP port 8080
                initTCPServer(8080);

                // Create a simple server on UDP port 8080
                initUDPServer(8080);
            }

        }
    }

    // Main loop :
    while(1)
    {
        result = GetBufferFromWifi(buffer,32,&size,&infoConnection);

        if( result == WIFI_OK )
        {
            // buffer stores the data received, size is the data lenght
            // and infoConnection store informations about the connexion.

            // for the example, a ping pong between client and server :

            if( infoConnection.isUdp == 0)
            {
                // We have received a wifi packet on the TCP server : echo back !
                SendBufferToRemoteClient(buffer,size,0,0);
            }
            else
            {
                // We have received a wifi packet on the UDP server : echo back !
                SendBufferToRemoteClient(buffer,size,infoConnection.ip,infoConnection.port);
            }

        }
    }


    return 0;
}

 * @endcode
 *
  * @par Create a wifi network.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8   result;
    UInt8   buffer[32];
    UInt32  size;
    WifiConnectionInfo infoConnection;

    UInt8 ip[4];
    UInt8 mask[4];
    UInt8 gateway[4];

    ip[0] = 192;
    ip[1] = 168;
    ip[2] = 1;
    ip[3] = 1;

    mask[0] = 255;
    mask[1] = 255;
    mask[2] = 255;
    mask[3] = 0;

    gateway[0] = 0;
    gateway[1] = 0;
    gateway[2] = 0;
    gateway[3] = 0;


    // Init cpu and robot :
    InitCpu();
    InitRobot();

    ﻿if( InitWifiHardware() == WIFI_OK)
    {
        // Wifi hardware is initialized, now create a wifi network:
        if( CreateWifiNetwork( "pobrobot",8,"mykey",5) == WIFI_OK )
        {
            // Now wifi is created with the name 'pobrobot', configure ip address :
            if( SetIpConfiguration(0,ip,mask,gateway) == WIFI_OK)
            {
                // Create a simple server on TCP port 8080
                initTCPServer(8080);

                // Create a simple server on UDP port 8080
                initUDPServer(8080);
            }

        }
    }

    // Main loop :
    while(1)
    {
        result = GetBufferFromWifi(buffer,32,&size,&infoConnection);

        if( result == WIFI_OK )
        {
            // buffer stores the data received, size is the data lenght
            // and infoConnection store informations about the connexion.

            // for the example, a ping pong between client and server :
            if( infoConnection.isUdp == 0)
            {
                // We have received a wifi packet on the TCP server : echo back !
                SendBufferToRemoteClient(buffer,size,0,0);
            }
            else
            {
                // We have received a wifi packet on the UDP server : echo back !
                SendBufferToRemoteClient(buffer,size,infoConnection.ip,infoConnection.port);
            }

        }
    }


    return 0;
}

 * @endcode
 */
#endif
#ifdef French_dox
/** \anchor wifi
 *
 * @brief Fonction module Wifi
 *
 * @file
 *
 * Vous pouvez ajouter un module Wifi dans le robot POB Robotics Suite.
 * Ce module vous permet de vous connecter sur un réseau sans fil TCP/IP.
 *
 * Vous pouvez créer au maximum 2 serveurs (qui vont attendrent 2 connexions distantes) et 2 connexions distantes vers un serveur distant !
 *
 * @par Rejoindre un réseau wifi.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8   result;
    UInt8   buffer[32];
    UInt32  size;
    WifiConnectionInfo infoConnection;


    // Initialisation du microcontroleur et du robot :
    InitCpu();
    InitRobot();

    ﻿if( InitWifiHardware() == WIFI_OK)
    {
        // Le matériel Wifi est initialisé, connection à un réseau wifi :
        if( JoinWifiNetwork( "MyWifiNetwork",13,"mykey",5,0)==WIFI_OK)
        {
            // Le robot est connecté sur le réseau 'MyWifiNetwork', on configure l'ip par le serveur dhcp du réseau :
            if( SetIpConfiguration(1,0,0,0) == WIFI_OK)
            {
                // On crée 2 serveurs, un serveur TCP sur le port 8080
                initTCPServer(8080);

                // et un second, un serveur UDP sur le port 8080.
                initUDPServer(8080);
            }

        }
    }

    // Boucle principale :
    while(1)
    {
        result = GetBufferFromWifi(buffer,32,&size,&infoConnection);

        if( result == WIFI_OK )
        {
            // buffer contient les données, size contient la taille des données
            // et infoConnection contient les informations sur la connection.

            // simplement pour l'exemple :
            if( infoConnection.isUdp == 0)
            {
                // On a reçu un paquet wifi sur le serveur TCP : on renvoie le même paquet !
                SendBufferToRemoteClient(buffer,size,0,0);
            }
            else
            {
                // On a reçu un paquet wifi sur le serveur UDP : on renvoie le même paquet !
                SendBufferToRemoteClient(buffer,size,infoConnection.ip,infoConnection.port);
            }

        }
    }


    return 0;
}

 * @endcode
 *
  * @par Création d'un réseau wifi avec le robot.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8   result;
    UInt8   buffer[32];
    UInt32  size;
    WifiConnectionInfo infoConnection;

    UInt8 ip[4];
    UInt8 mask[4];
    UInt8 gateway[4];

    ip[0] = 192;
    ip[1] = 168;
    ip[2] = 1;
    ip[3] = 1;

    mask[0] = 255;
    mask[1] = 255;
    mask[2] = 255;
    mask[3] = 0;

    gateway[0] = 0;
    gateway[1] = 0;
    gateway[2] = 0;
    gateway[3] = 0;


    // Initialisation du microcontroleur et du robot :
    InitCpu();
    InitRobot();

    ﻿if( InitWifiHardware() == WIFI_OK)
    {
        // La puce Wifi du robot est initialisé, on crée le réseau wifi :
        if( CreateWifiNetwork( "pobrobot",8,"mykey",5) == WIFI_OK )
        {
            // Un nouveau réseau wifi est crée avec le nom 'pobrobot', on configure l'adresse ip manuellement :
            if( SetIpConfiguration(0,ip,mask,gateway) == WIFI_OK)
            {
                // On crée 2 serveurs, un TCP sur le port 8080
                initTCPServer(8080);

                // et le second, un serveur UDP sur le port 8080
                initUDPServer(8080);
            }

        }
    }

   // Boucle principale :
    while(1)
    {
        result = GetBufferFromWifi(buffer,32,&size,&infoConnection);

        if( result == WIFI_OK )
        {
            // buffer contient les données, size contient la taille des données
            // et infoConnection contient les informations sur la connection.

            // Pour l'exemple, on crée un ping-pong avec le client :

            if( infoConnection.isUdp == 0)
            {
                // On a reçu un paquet wifi sur le serveur TCP : on renvoie le même paquet !
                SendBufferToRemoteClient(buffer,size,0,0);
            }
            else
            {
                // On a reçu un paquet wifi sur le serveur UDP : on renvoie le même paquet !
                SendBufferToRemoteClient(buffer,size,infoConnection.ip,infoConnection.port);
            }

        }
    }

    return 0;
}

 * @endcode
 */
#endif
#ifndef RS007_WIFI_H
#define RS007_WIFI_H

#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_OK                 0       /**< Wifi module ok */
#define WIFI_ERROR              1       /**< Last operation failed */
#define WIFI_NO_PACKET          2       /**< No packet receveid */
#define WIFI_CONNECTION_CLOSED  3       /**< Connection closed by remote host */
#define WIFI_NO_CLIENT_CONNECTED 4      /**< No client connected */
#define WIFI_NO_HARDWARE        5       /**< No wifi hardware detected */
#define WIFI_TIMEOUT            6       /**< Operation on wifi timeout */
#define WIFI_BUFFER_OVERFLOW    7       /**< A buffer overflow during reception */

/** @brief Wifi information structure.
 */
typedef struct _wifi_robot_
{
    UInt8 mac[6];       /**< mac address of robot */
    UInt8 ip[4];        /**< ip address of robot */
} WifiRobotInfo;

/** @brief Wifi connection structure.
 */
typedef struct _ip_remote_connection_
{
    UInt8   ip[4];			/**< ip address of remote host */
    UInt16  port;			/**< port of remote host */
    UInt8   socket;			/**< socket identifier for this connection */
    UInt8   isUdp;			/**< is this an udp connection? */
	UInt8   isFromServer;   /**< is this from a server or a client? */
} WifiConnectionInfo;

#ifdef English_dox
/** @brief Init the Wifi hardware chip.
 *
 * @return WIFI_OK if success, else error code.
 */
#endif
#ifdef French_dox
/** @brief Initialiser la puce matériel du Wifi.
 *
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 InitWifiHardware(void);

#ifdef English_dox
/** @brief Create a wifi network.
 *
 * Create a ad-hoc wifi network: You can connect to this network with your computer
 *
 * @param SSID          Name of the network to be created.
 * @param SSIDLength    Lenght of the name.
 * @param key           Security key.
 * @param keyLength     Length of the security key.
 * @return WIFI_OK if sucess, else error code.
 */
#endif
#ifdef French_dox
/** @brief Création d'un réseau Wifi.
 *
 * Création d'un réseau ad-hoc wifi sur lequel vous pouvez vous connecter avec votre ordinateur :
 * Le robot fait office de réseau wifi.
 *
 * @param SSID          Nom du réseau.
 * @param SSIDLength    Longueur du nom.
 * @param key           Clé de sécurité.
 * @param keyLength     Longueur de la clé.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 CreateWifiNetwork(UInt8* SSID,UInt32 SSIDLength,UInt8* key,UInt32 keyLength);

#ifdef English_dox
/** @brief Join a wifi network.
 *
 * Connect the robot to a wireless wifi network.
 *
 * @param SSID          Name of the network to be joined.
 * @param SSIDLength    Length of the network's name.
 * @param key           Security key.
 * @param keyLength     Length of the security key.
 * @param channel       Wifi channel number: 0 if unknown, else canal number.
 * @return WIFI_OK if sucess, else error code.
 */
#endif
#ifdef French_dox
/** @brief Rejoindre un réseau Wifi.
 *
 * Connecter le robot à un réseau sans fil Wifi.
 *
 * @param SSID          Nom du réseau à rejoindre.
 * @param SSIDLength    Longueur du nom.
 * @param key           Clé de sécurité.
 * @param keyLength     Longueur de la clé.
 * @param channel       Canal radio wifi : 0 si inconnue, sinon numéro du canal.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 JoinWifiNetwork(UInt8 *SSID,UInt32 SSIDlength, UInt8* key, UInt32 keyLength, UInt8 channel);

#ifdef English_dox
/** @brief Get buffer from the wifi chip.
 *
 * @param buffer        Buffer where store received bytes.
 * @param bufferSize    Size of previous buffer.
 * @param [out] length  Number of bytes received (if any).
 * @param [out] info    Connection information.
 * @return WIFI_OK if a packet is received else error code.
 */
#endif
#ifdef French_dox
/** @brief Recevoir des données depuis le réseau Wifi.
 *
 * @param buffer        Tableau où stocker les octets reçus.
 * @param bufferSize    Taille du tableau.
 * @param [out] length  Nombre d'octets reçus.
 * @param [out] info    Information sur la réception.
 * @return WIFI_OK si un paquet est reçu, sinon code d'erreur.
 */
#endif
extern UInt8 GetBufferFromWifi( UInt8 * buffer, UInt32 bufferSize, UInt32 * length, WifiConnectionInfo *info);

#ifdef English_dox
/** @brief Send a buffer to the TCP/IP network to a remote client.
 *
 * The client must be connected to a server on the robot.
 *
 * @param buffer    Buffer to send.
 * @param size      Size of buffer to send.
 * @param ip        Must be 0 if you are sending to a tcp connection, else ip of the client.
 * @param port      Must be 0 if you are sending to a tcp connection, else port of the client.
 * @return WIFI_OK if packet is send, else error code.
 */
#endif
#ifdef French_dox
/** @brief Envoyer des octets à un client distant sur le réseau Wifi.
 *
 * Le client doit être connecté sur un serveur du robot.
 *
 * @param buffer    Tableau à envoyer.
 * @param size      Nombre d'octets à envoyer.
 * @param ip        Doit être à 0 si vous envoyer sur une connection TCP, sinon adresse ip du client.
 * @param port      Doit être à 0 si vous envoyer sur une connection TCP, sinon port du client.
 * @return WIFI_OK si le paquet est envoyé, sinon code d'erreur.
 */
#endif
extern UInt8 SendBufferToRemoteClient(UInt8* buffer, UInt32 size, UInt8 *ip, UInt16 port);

#ifdef English_dox
/** @brief Send a buffer to a remote server.
 *
 * @param buffer    Buffer to send.
 * @param size      Size of buffer to send.
 * @param ip        Must be 0 if you are sending to a TCP connection, else ip address of the server.
 * @param port      Must be 0 if you are sending to a TCP connection, else port of the server.
 * @return WIFI_OK if packet is send, else error code.
 */
#endif
#ifdef French_dox
/** @brief Envoyer des octets à un serveur distant sur le réseau Wifi.
 *
 * @param buffer    Tableau à envoyer.
 * @param size      Nombre d'octets à envoyer.
 * @param ip        Doit être à 0 si vous envoyer sur une connection TCP, sinon adresse ip du client.
 * @param port      Doit être à 0 si vous envoyer sur une connection TCP, sinon port du client.
 * @return WIFI_OK is le paquet est envoyé, sinon code d'erreur.
 */
#endif
extern UInt8 SendBufferToRemoteServer(UInt8* buffer, UInt32 size, UInt8 *ip, UInt16 port);

#ifdef English_dox
/** @brief Get wifi information of the robot.
 *
 * @return A pointer to the information.
 */
#endif
#ifdef French_dox
/** @brief Récupére les informations wifi du robot.
 *
 * @return Un pointeur sur les informations.
 */
#endif
extern WifiRobotInfo * GetWifiRobotInfo(void);

#ifdef English_dox
/** @brief Set ip configuration of the wifi chip.
 *
 * @param dhcp      Set 1 to request an ip address from a dhcp server, else 0 to set your own ip configuration.
 * @param ip        Ip address of the wifi module.
 * @param subnet    Subnetwork mask.
 * @param gateway   Ip address of the gateway for the wifi module.
 * @return WIFI_OK if sucess, else error code.
 */
#endif
#ifdef French_dox
/** @brief Configure l'adresse ip du module wifi.
 *
 * @param dhcp      Mettre 1 pour demander la configuration à un serveur dhcp, sinon 0 pour mettre votre propre configuration.
 * @param ip        Adresse ip du module Wifi.
 * @param subnet    Masque sous réseau.
 * @param gateway   Adresse ip de la passerelle.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 SetIpConfiguration( UInt8 dhcp, UInt8 * ip, UInt8 * subnet, UInt8 * gateway);

#ifdef English_dox
/** @brief Init a UDP server on the specified port.
 *
 * @param port      Server's port.
 * @return WIFI_OK if success, else error code.
 */
#endif
#ifdef French_dox
/** @brief Crée un serveur UDP sur le port spécifié.
 *
 * @param port      Port du serveur.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 initUDPServer(UInt16 port);

#ifdef English_dox
/** @brief Init a TCP server on the specified port.
 *
 * @param port      Server's port.
 * @return WIFI_OK if success, else error code.
 */
#endif
#ifdef French_dox
/** @brief Crée un serveur TCP sur le port spécifié.
 *
 * @param port      Port du serveur.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 initTCPServer(UInt16 port);

#ifdef English_dox
/** @brief Connect to a remote UDP server.
 *
 * @param ip    Ip address of server.
 * @param port  Port of server.
 * @return WIFI_OK if success, else error code.
 */
#endif
#ifdef French_dox
/** @brief Se connecter sur un serveur UDP distant.
 *
 * @param ip    Adresse ip du serveur.
 * @param port  Port du serveur.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 connectToUDPServer(UInt8 * ip, UInt16 port);

#ifdef English_dox
/** @brief Connect to a remote TCP server.
 *
 * @param ip    Ip address of server.
 * @param port  Port of server.
 * @return WIFI_OK if success, else error code.
 */
#endif
#ifdef French_dox
/** @brief Se connecter sur un serveur TCP distant.
 *
 * @param ip    Adresse ip du serveur.
 * @param port  Port du serveur.
 * @return WIFI_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 connectToTCPServer(UInt8 * ip, UInt16 port);

#ifdef English_dox
/** @brief Get Wifi channel number.
 *
 * Warning, you must use this function when you are connected to a wifi network!
 *
 * @return Channel number.
 */
#endif
#ifdef French_dox
/** @brief Récupére le numéro du canal radio Wifi.
 *
 * Attention, cette fonction est à utiliser sur un réseau connecté !
 *
 * @return Numéro canal.
 */
#endif
 extern UInt8 GetWifiChannel(void);


extern void HaltWifiHardware(void);

#ifdef __cplusplus
 }
#endif

#endif
