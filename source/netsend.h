
bool USend(int connType, const char* buf, int len) {
	return (connType==CLIENT)?send(buf, len):sendTo(buf, len);
}

void NetSend() {	
	static int s_packetId = g_packetId;

	switch (s_packetId) {
	case 0:
		player1.nextPacketId = g_packetId;
	 	USend(connType,(const char*)&player1, sizeof(player1));  	
	 	break;
	case 1:
		gdata.nextPacketId = g_packetId;
 		USend(connType,(const char*)&gdata, sizeof(gdata));  	
	 	break;
	case 2:
		myState.nextPacketId = g_packetId;
 		USend(connType,(const char*)&myState, sizeof(myState));  	
	 	break;	 	
	 	
	}
	
	s_packetId = g_packetId;
	g_packetId = 0;
}
 
