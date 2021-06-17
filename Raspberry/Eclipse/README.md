# Configuration librairie

Pour pigpio, pthread:
	
	-Cross GCC/G++ Compiler
		|
		|-->Includes
			|
			|-->$HOME/rootfs/usr/local/include
	-Cross GCC/G++ Linker
                |  
                |-->Librairies
                        | 
                        |-->pigpio, pthread
                        | 
                        |-->$HOME/rootfs/usr/local/lib

Pour paho (MQTT):

        -Cross GCC/G++ Compiler
                |  
                |-->Includes
                        | 
                        |-->$HOME/rootfs/usr/local/include
        -Cross GCC/G++ Linker
                |
                |-->Librairies
                        |
                        |-->paho-mqttpp3, paho-mqtt3a, paho-mqtt3as
			|   ssl, crypto, pthread                        
                        |
                        |-->$HOME/rootfs/usr/local/lib
			    /opt/cross-pi-gcc/arm-linux-gnueabihf/lib
			    $HOME/rootfs/usr/lib/arm-linux-gnueabihf
			(! ATTENTION DE BIEN RESPCTER L'ORDRE DES DOSSIERS !) 
		
