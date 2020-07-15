char b;

bool UReceive (int connType, char* buf, int len) {
		return  (connType==CLIENT)?receive(buf, len):receiveFrom(buf, len);
}

void NetListen() {
	static int s_packetId = 0;

	Player remotePlayer;
	GameObject gobj;
	PlayerState remotePlayerState;

	switch (s_packetId) {
	case 0:
		if (UReceive(connType, (char *)&remotePlayer, sizeof(remotePlayer))) {
			player2 = remotePlayer;
			s_packetId = remotePlayer.nextPacketId;
		} else exit(0);
			break;
	case 1:
		if (UReceive(connType, (char *)&gobj, sizeof(gobj))) {
			objects.push_back(gobj);			
			s_packetId = gobj.nextPacketId;
		} else exit(0);
			break;
	
	case 2:
		if (UReceive(connType, (char *)&remotePlayerState, sizeof(remotePlayerState))) {
			oppState = remotePlayerState;		
			s_packetId = remotePlayerState.nextPacketId;
		} else exit(0);
			break;
		
	
	}
}

 
 
