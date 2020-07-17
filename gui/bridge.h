#ifndef BRIDGE_HEADER_FILE
#define BRIDGE_HEADER_FILE

#include "constants.h"

BRIDGE * create_bridge( int length, int weight, enum bridgePosition position, int scheduler);
BRIDGE * load_bridge(enum bridgePosition pos);
int can_cross(BRIDGE * myBridge, ALIEN alienMoving);


#endif

