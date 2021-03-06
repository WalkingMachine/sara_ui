#include "CThreadRos.h"

CThreadRos::~CThreadRos() {
	this->exit();
}

void CThreadRos::run(){
	CPU.enrNumberOfCore = 0;
	CPU.pCPUCoresUsage = NULL;
	
	ROS_INFO("Thread START");
	
	subscribeROS();
	
	ROS_INFO("Ros Subscription to Diagnostics");
	
	while (ros::ok()) {
        ros::spinOnce();
	}
	
	ROS_INFO("Thread END");
}

void CThreadRos::callbackMessageReceived(const diagnostic_msgs::DiagnosticArray message) {
	//if the hardware related data is the main computer of SARA
	if (!message.status[0].hardware_id.compare(HARDWARE_ID)) {
		//read all status of the message
		for (std::vector<diagnostic_msgs::DiagnosticStatus>::const_iterator StatusIterator = message.status.begin();
		     StatusIterator != message.status.end(); ++StatusIterator) {
			if (!StatusIterator->name.compare("CPU_Usage")) {
				//Update Number of Cores
				CPU.enrNumberOfCore = std::stoi(StatusIterator->message);
				
				//Create new array of core
				float *enrTabCoresUsage = (float *) malloc(sizeof(float) * CPU.enrNumberOfCore);
				
				//reading each core usage
				for (int iCoreNumber = 0; iCoreNumber < CPU.enrNumberOfCore; iCoreNumber++) {
					enrTabCoresUsage[iCoreNumber] = 100 - std::stod(StatusIterator->values[iCoreNumber].value);
				}
				
				//link array with CPU struct
				CPU.pCPUCoresUsage = enrTabCoresUsage;
				
				//execute CPU update signal
				updateCPU(&CPU);
			} else if (!StatusIterator->name.compare("Memory_Usage")) {
				//Update Memory Usages
				Memory.Memory_Total = std::stoi(StatusIterator->values[0].value);
				Memory.Memory_Used = Memory.Memory_Total - std::stoi(StatusIterator->values[1].value);
				Memory.Memory_Usage = Memory.Memory_Used * 100 / Memory.Memory_Total;
				//Update Swap Usages
				Memory.Swap_Total = std::stoi(StatusIterator->values[2].value);
				Memory.Swap_Used = Memory.Swap_Total - std::stoi(StatusIterator->values[3].value);
				Memory.Swap_Usage = Memory.Swap_Used * 100 / Memory.Swap_Total;
				
				//execute memory update signal
				updateMemory(&Memory);
			} else if (!StatusIterator->name.compare("Temperature_Sensors")) {
				//clear sensors arrays
				Temperature_Sensors.enrCpuSensors.clear();
				Temperature_Sensors.enrSensors.clear();
				
				//read all sensors values received
				for (std::vector<diagnostic_msgs::KeyValue>::const_iterator ValueIterator = StatusIterator->values.begin();
				     ValueIterator != StatusIterator->values.end(); ++ValueIterator) {
					//copy value data in sensor buffer
					SENSOR_TYPE enrSensor;
					enrSensor.strName = QString::fromStdString(ValueIterator->key);
					enrSensor.strValue = QString::fromStdString(ValueIterator->value);
					
					//if it is CPU temperatures :
					if (enrSensor.strName.contains(QRegExp("^CPU.*$"))) {
						//push in CPU sensors array
						Temperature_Sensors.enrCpuSensors.push_back(enrSensor);
					} else {
						//push in other sensors array
						Temperature_Sensors.enrSensors.push_back(enrSensor);
					}
					
				}
				
				//execute sensors update signal
				updateTemperatureSensors(&Temperature_Sensors);
			}
		}
	}
}

void CThreadRos::callbackLogReceived(const std_msgs::String message){
    addLog(QString::fromStdString(message.data));
}

void CThreadRos::subscribeROS() {
	ROS_INFO("Subscript");
    //subscribe to the diagnostics topic
    subscriber = nh.subscribe("diagnostics", 1, &CThreadRos::callbackMessageReceived, this);

    //subscribe to the logger topic
    logSubscriber = nh.subscribe("ui/logs", 1, &CThreadRos::callbackLogReceived, this);

    //advertise the Continue button publisher
    continuePublisher = nh.advertise<std_msgs::Bool>("ui/continue", 5);
}

void CThreadRos::unsubscribeROS() {
	subscriber.shutdown();
    logSubscriber.shutdown();
}

void CThreadRos::publishContinue(bool bMessage){
    //generate boolean standart message
    std_msgs::Bool message;
    //write true in the message
    message.data = bMessage;
    //pubkish the message
    continuePublisher.publish(message);
}
