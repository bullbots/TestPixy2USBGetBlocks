//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
#include <jni.h>
#include <iostream>
#include <sstream>

#include "RoboRioPixy2USBJNI.h"
#include "libpixyusb2.h"

Pixy2 pixy;

JNIEXPORT jint JNICALL Java_frc_robot_vision_Pixy2USBJNI_pixy2USBInit(JNIEnv *env, jobject thisObj) {
   std::cout << "pixy2 usb init" << std::endl;
   return pixy.init();
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2USBJNI_pixy2USBGetVersion(JNIEnv *env, jobject thisObj) {
   std::cout << "pixy2 usb get version" << std::endl;
   pixy.version->print();
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2USBJNI_pixy2USBLampOn(JNIEnv *env, jobject thisObj) {
   std::cout << "pixy2 usb Lamp On" << std::endl;
   pixy.setLamp(0x01, 0x00);
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2USBJNI_pixy2USBLampOff(JNIEnv *env, jobject thisObj) {
   std::cout << "pixy2 usb Lamp Off" << std::endl;
   pixy.setLamp(0x00, 0x00);
   return;
}

JNIEXPORT jstring JNICALL Java_frc_robot_vision_Pixy2USBJNI_pixy2USBGetBlocks(JNIEnv *env, jobject thisObj)
{
  int  Block_Index;

  // Query Pixy for blocks //
  pixy.ccc.getBlocks();

  std::stringstream ss;

  // Were blocks detected? //
  if (pixy.ccc.numBlocks)
  {
    // Blocks detected - print them! //

    // Uncomment for debug
   //  printf ("Detected %d block(s)\n", pixy.ccc.numBlocks);

    for (Block_Index = 0; Block_Index < pixy.ccc.numBlocks; ++Block_Index)
    {
      // printf ("  Block %d: ", Block_Index + 1);
      ss << "block " << Block_Index + 1 << " : ";
      ss << pixy.ccc.blocks[Block_Index].str();
      if (Block_Index < pixy.ccc.numBlocks-1) {
          ss << std::endl;
      }
    //   pixy.ccc.blocks[Block_Index].print();
    }
  }
  return env->NewStringUTF(ss.str().c_str());
}

