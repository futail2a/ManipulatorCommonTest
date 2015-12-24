// -*- C++ -*-
/*!
 * @file  ManipulatorCommonTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "ManipulatorCommonTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* manipulatorcommontest_spec[] =
  {
    "implementation_id", "ManipulatorCommonTest",
    "type_name",         "ManipulatorCommonTest",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Sugar Sweet Robotics",
    "category",          "Tes",
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
  m_manipMiddlePort.registerConsumer("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_manipMiddle);
  m_manipCommonPort.registerConsumer("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_manipCommon);
  
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


RTC::ReturnCode_t ManipulatorCommonTest::onExecute(RTC::UniqueId ec_id)
{
  std::cout << "Input Command (h for help):" << std::ends;
  char c;
  std::cin >> c;
  rewind(stdin);
  fflush(stdin);
  JARA_ARM::CarPosWithElbow_var pos = new JARA_ARM::CarPosWithElbow();//(new JARA_ARM::CarPosWithElbow_var());
  switch(c) {
  case 'v':
    std::cout << "getFeedbackPosCartesian" << std::endl;
    m_manipMiddle->getFeedbackPosCartesian(pos);
    std::cout << "getFeedbackPosCartesian:" << std::endl;
    // printf("carPos: %4.4f %4.4f %4.4f %4.4f\n", pos->carPos[0][0], pos->carPos[0][1], pos->carPos[0][2], pos->carPos[0][3]);
    break;
  default:
    printf("Unknown Command %c\n", c);
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


