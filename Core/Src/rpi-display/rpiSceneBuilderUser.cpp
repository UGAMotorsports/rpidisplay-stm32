/*
 * rpiSceneBuilderUser.cpp
 *
 *  Created on: May 2, 2025
 *      Author: bhargav
 */

#include "rpiSceneBuilderUser.h"

#include "rpiDisplaySceneBuilder.h"
#include "FreeSans18pt7b.h"
#include "FreeMonoBold24pt7b.h"
#include "splashimage.h"

char buffer[18] = "hello hello hello";
DisplayObject* objects[3] = {
		new OutlineEllipseObject(240, 160, 100, 50, 0xF000, CENTER_OBJECT, 2),
		new StringObject(240, 160, 0xFFFF, FREE_SANS_18PT7B, CENTER_OBJECT, buffer, 3),
		new PointObject(240, 160, 0x001F, 4)
};
Scene myScene(objects, 3);

char rpmresult[17] = "not recieved rpm";
char tempresult[18] = "not recieved temp";
DisplayObject* otherobjects[2] = {
		new StringObject(240, 160, 0xFFFF, FREE_MONO_BOLD_24PT7B, CENTER_OBJECT, rpmresult, 1),
		new StringObject(240, 100, 0xFFFF, FREE_SANS_18PT7B, CENTER_OBJECT, tempresult, 3)
};
Scene myScene2(otherobjects, 2);

DisplayObject* splashobjects[3] = {
		new ImageObject(epd_bitmap_Screenshot_from_2025_05_03_23_43_00, SPLASH_LENGTH, SPLASH_HEIGHT, 240, 160, CENTER_OBJECT, 2)
};
Scene splashScene(splashobjects, 1);

void dostring() {
	myScene.drawScene();
	myScene.setScene(objects, 3);
}

void dootherstring() {
	myScene2.drawScene();
	myScene2.setScene(otherobjects, 2);
}

void dosplashscene() {
	splashScene.drawScene();
	splashScene.setScene(splashobjects, 1);
}

