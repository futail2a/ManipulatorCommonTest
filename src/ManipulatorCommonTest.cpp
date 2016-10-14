// -*- C++ -*-
/*!
 * @file  ManipulatorCommonTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "ManipulatorCommonTest.h"
#define _USE_MATH_DEFINES
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* manipulatorcommontest_spec[] =
  {
    "implementation_id", "ManipulatorCommonTest",
    "type_name",         "ManipulatorCommonTest",
    "description",       "ManipulatorCommonInterface Tester",
    "version",           "1.0.0",
    "vendor",            "Sugar Sweet Robotics",
    "category",          "Manipulator",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ManipulatorCommonTest::ManipulatorCommonTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_manipMiddlePort("manipMiddle"),
    m_manipCommonPort("manipCommon")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ManipulatorCommonTest::~ManipulatorCommonTest()
{
}



RTC::ReturnCode_t ManipulatorCommonTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_manipMiddlePort.registerConsumer("JARA_ARM_ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_manipMiddle);
  m_manipCommonPort.registerConsumer("JARA_ARM_ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_manipCommon);
  
  // Set CORBA Service Ports
  addPort(m_manipMiddlePort);
  addPort(m_manipCommonPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ManipulatorCommonTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorCommonTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorCommonTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ManipulatorCommonTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ManipulatorCommonTest::onDeactivated(RTC::UniqueId ec_id)
{
  
  return RTC::RTC_OK;
}

#define RADIANS(x) (x)/180.0*M_PI

void show_help() {
	printf(
		" l : show position matrix\n"
		" o : servo ON\n"
		" i : servo OFF\n"
		" f : move right\n"
		" s : move left\n"
		" e : move forward\n"
		" c : move backward\n"
		" x : rotate CW\n"
		" t : set software limit"
		);
}


RTC::ReturnCode_t ManipulatorCommonTest::onExecute(RTC::UniqueId ec_id)
{
  std::cout << "Input Command (h for help):" << std::ends;
  char c;
  std::cin >> c;
  rewind(stdin);
  fflush(stdin);
  JARA_ARM::CarPosWithElbow targetPos;
  targetPos.elbow = 0;
  targetPos.carPos[0][0] = 1; targetPos.carPos[0][1] = 0; targetPos.carPos[0][2] = 0; targetPos.carPos[0][3] = 0;
  targetPos.carPos[1][0] = 0; targetPos.carPos[1][1] = 1; targetPos.carPos[1][2] = 0; targetPos.carPos[1][3] = 0;
  targetPos.carPos[2][0] = 0; targetPos.carPos[2][1] = 0; targetPos.carPos[2][2] = 1; targetPos.carPos[2][3] = 0;

  JARA_ARM::CarPosWithElbow_var pos = new JARA_ARM::CarPosWithElbow();//(new JARA_ARM::CarPosWithElbow_var());
 /*
  JARA_ARM::JointPos_var jpos = new JARA_ARM::JointPos(); 
  
  JARA_ARM::LimitSeq_var jointLimit = new JARA_ARM::LimitSeq[6];
  jointLimit[0].upper = 2.6;
  jointLimit[0].lower = -2.6;
  jointLimit[1].upper = 2.2;
  jointLimit[1].lower = -1.0;
  jointLimit[2].upper = 2.5;
  jointLimit[2].lower = -0.16;
  jointLimit[3].upper = 2.6;
  jointLimit[3].lower = -2.6;
  jointLimit[4].upper = 2.2;
  jointLimit[4].lower = -1.5;
  jointLimit[5].upper = 2.8;
  jointLimit[5].lower = -2.8;

  m_manipCommon->setSoftLimitJoint(jointLimit);
*/

  switch(c) {
  case 'l':
    std::cout << "getFeedbackPosCartesian" << std::endl;
    m_manipMiddle->getFeedbackPosCartesian(pos);
    printf("carPos: %4.4f %4.4f %4.4f %4.4f\n", pos->carPos[0][0], pos->carPos[0][1], pos->carPos[0][2], pos->carPos[0][3]);
	printf("        %4.4f %4.4f %4.4f %4.4f\n", pos->carPos[1][0], pos->carPos[1][1], pos->carPos[1][2], pos->carPos[1][3]);
	printf("        %4.4f %4.4f %4.4f %4.4f\n", pos->carPos[2][0], pos->carPos[2][1], pos->carPos[2][2], pos->carPos[2][3]);
	break;
  case 'o':
	  std::cout << "servoON" << std::endl;
	  m_manipCommon->servoON();
	  break;
  case 'i':
	  std::cout << "servoOFF" << std::endl;
	  m_manipCommon->servoOFF();
	  break;
  case 'f':
	  std::cout << "move right" << std::endl;
	  targetPos.carPos[1][3] = -0.01;
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case 's':
	  std::cout << "move left" << std::endl;
	  targetPos.carPos[1][3] = +0.01;
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case 'e':
	  std::cout << "move forward" << std::endl;
	  targetPos.carPos[0][3] = +0.01;
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case 'c':
	  std::cout << "move backward" << std::endl;
	  targetPos.carPos[0][3] = -0.01;
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case 'x':
	  std::cout << "Z axis rotateCW" << std::endl;
	  targetPos.carPos[0][0] = cos(RADIANS(5));
	  targetPos.carPos[0][1] = -sin(RADIANS(5));
	  targetPos.carPos[1][0] = sin(RADIANS(5));
	  targetPos.carPos[1][1] = cos(RADIANS(5));
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case 'v':
	  std::cout << "Z axis rotateCCW" << std::endl;
	  targetPos.carPos[0][0] = cos(RADIANS(-5));
	  targetPos.carPos[0][1] = -sin(RADIANS(-5));
	  targetPos.carPos[1][0] = sin(RADIANS(-5));
	  targetPos.carPos[1][1] = cos(RADIANS(-5));
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case '@':
	  std::cout << "Y axis rotateCW" << std::endl;
	  targetPos.carPos[0][0] = cos(RADIANS(5));
	  targetPos.carPos[0][2] = -sin(RADIANS(5));
	  targetPos.carPos[2][0] = sin(RADIANS(5));
	  targetPos.carPos[2][2] = cos(RADIANS(5));
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
  case '[':
	  std::cout << "Y axis rotateCCW" << std::endl;
	  targetPos.carPos[0][0] = cos(RADIANS(-5));
	  targetPos.carPos[0][1] = -sin(RADIANS(-5));
	  targetPos.carPos[2][0] = sin(RADIANS(-5));
	  targetPos.carPos[2][1] = cos(RADIANS(-5));
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
	  
  case ':':
	  m_manipCommon->getFeedbackPosJoint(jpos);
	  printf("current joint number: %d\n", jpos->length());
	  printf("current joint angles: %4.4f %4.4f %4.4f %4.4f %4.4f %4.4f\n", jpos[0],jpos[1],jpos[2],jpos[3],jpos[4],jpos[5]);
	  std::cout << "enter each angles" << std::endl;
	  std::cin >> jpos[0];
	  std::cin >> jpos[1];
	  std::cin >> jpos[2];
	  std::cin >> jpos[3];
	  std::cin >> jpos[4];
	  std::cin >> jpos[5];

	  m_manipMiddle->movePTPJointAbs(jpos);
	  break;
	  
  case 'w':
	  std::cout << "Up" << std::endl;
	  targetPos.carPos[2][3] = +0.01;
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;

  case 'r':
	  std::cout << "Down" << std::endl;
	  targetPos.carPos[2][3] = -0.01;
	  m_manipMiddle->movePTPCartesianRel(targetPos);
	  break;
	  	  
  case 'y':
	  std::cout << "Close Gripper" << std::endl;
	  //m_manipMiddle->closeGripper();
	  m_manipMiddle->moveGripper(70);
	  break;
  case 'n':
	  std::cout << "Open Gripper" << std::endl;
	  m_manipMiddle->openGripper();
	  break;

  case 'p':
	  m_manipMiddle->setSpeedCartesian(10);
	  break;
  case ';':
	  m_manipMiddle->setSpeedCartesian(50);
	  break;

 /* case 't':
	  JARA_ARM::LimitValue limitx, limity, limitz;
	  limitx.upper = 0.5;
	  limitx.lower = -0.5;
	  limity.upper = 0.5;
	  limity.lower = -0.5;
	  limitz.upper = 0.5;
	  limitz.lower = -0.5;

	  m_manipMiddle->setSoftLimitCartesian(limitx, limity, limitz);
	  */

  case 'h':
  default:
	  show_help();
    break;
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ManipulatorCommonTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorCommonTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorCommonTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorCommonTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorCommonTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ManipulatorCommonTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(manipulatorcommontest_spec);
    manager->registerFactory(profile,
                             RTC::Create<ManipulatorCommonTest>,
                             RTC::Delete<ManipulatorCommonTest>);
  }
  
};


