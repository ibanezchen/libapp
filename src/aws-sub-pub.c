/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file subscribe_publish_sample.c
 * @brief simple MQTT publish and subscribe on the same topic
 *
 * This example takes the parameters from the aws_iot_config.h file and establishes a connection to the AWS IoT MQTT Platform.
 * It subscribes and publishes to the same topic - "sdkTest/sub"
 *
 * If all the certs are correct, you should see the messages received by the application in a loop.
 *
 * The application takes in the certificate path, host name , port and the number of times the publish should happen.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#include <hcos/core.h>
#include <hcos/task.h>
#include "plt.h"
#include "plt-wifi.h"

#define MBEDTLS_PLATFORM_MEMORY
#include <mbedtls/platform.h>

#define IOT_INFO
#define IOT_WARN
#define IOT_ERROR
#define IOT_DEBUG
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_config.h"
#include "aws_iot_mqtt_client.h"
#include "cert_platform.h"

#define xstr(s) str(s)
#define str(s) #s

extern char root_crt[];
extern char dev_crt[];
extern char dev_key[];

char * keys[] = {
	root_crt, dev_crt, dev_key
};

aws_key_t* aws_key_init(aws_key_t* o, int type)
{
	char* key = 0;
	if(type > 2)
		return 0;
	key = keys[type];
	o->type= type;
	o->sz = strlen(key) + 1;
	o->raw= (unsigned char*)key;
	return o;
}

void MQTTcallbackHandler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
						 IoT_Publish_Message_Params *params, void *pData) {
	INFO("Subscribe callback");
	INFO("%.*s\t%.*s", topicNameLen, topicName, (int)params->payloadLen, (char*)params->payload);
}

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
	WARN("MQTT Disconnect");
	IoT_Error_t rc = FAILURE;
	if(NULL == data) {
		return;
	}

	AWS_IoT_Client *client = (AWS_IoT_Client *)data;
	if(aws_iot_is_autoreconnect_enabled(client)){
		INFO("Auto Reconnect is enabled, Reconnecting attempt will start now");
	}else{
		WARN("Auto Reconnect not enabled. Starting manual reconnect...");
		rc = aws_iot_mqtt_attempt_reconnect(client);
		if(NETWORK_RECONNECTED == rc){
			WARN("Manual Reconnect Successful");
		}else{
			WARN("Manual Reconnect Failed - %d", rc);
		}
	}
}

/**
 * @brief Default MQTT HOST URL is pulled from the aws_iot_config.h
 */
char HostAddress[255] = AWS_IOT_MQTT_HOST;

/**
 * @brief Default MQTT port is pulled from the aws_iot_config.h
 */
uint32_t port = AWS_IOT_MQTT_PORT;

/**
 * @brief This parameter will avoid infinite loop of publish and exit the program after certain number of publishes
 */
uint32_t publishCount = 0;

AWS_IoT_Client client;

extern unsigned _HZ;

void aws_sub_pub()
{
	IoT_Error_t rc = FAILURE;
	int32_t i = 0;
	bool infinitePublishFlag = true;

	strcpy(HostAddress, xstr(AWS_IOT_AP));
	INFO("\nAWS IoT SDK Version %d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

//	getcwd(CurrentWD, sizeof(CurrentWD));
//	snprintf(rootCA, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_ROOT_CA_FILENAME);
//	snprintf(clientCRT, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_CERTIFICATE_FILENAME);
//	snprintf(clientKey, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_PRIVATE_KEY_FILENAME);
//	DEBUG("rootCA %s", rootCA);
//	DEBUG("clientCRT %s", clientCRT);
//	DEBUG("clientKey %s", clientKey);

	IoT_Client_Init_Params mqttInitParams;
	mqttInitParams.enableAutoReconnect = false; // We enable this later below
	mqttInitParams.pHostURL =  HostAddress;
	mqttInitParams.port = port;
//	mqttInitParams.pRootCALocation = rootCA;
//	mqttInitParams.pDeviceCertLocation = clientCRT;
//	mqttInitParams.pDevicePrivateKeyLocation = clientKey;
	mqttInitParams.mqttCommandTimeout_ms = 20000;
	mqttInitParams.tlsHandshakeTimeout_ms = 20000;
	mqttInitParams.isSSLHostnameVerify = false;
	mqttInitParams.disconnectHandler = disconnectCallbackHandler;
	mqttInitParams.disconnectHandlerData = (void *)&client;

	rc = aws_iot_mqtt_init(&client, &mqttInitParams);
	if(SUCCESS != rc) {
		ERROR("aws_iot_mqtt_init returned error : %d ", rc);
	}

	IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;

	connectParams.keepAliveIntervalInSec = 10;
	connectParams.isCleanSession = true;
	connectParams.MQTTVersion = MQTT_3_1_1;
	connectParams.pClientID = "CSDK-test-device";
	connectParams.isWillMsgPresent = false;

	INFO("Connecting...");
	rc = aws_iot_mqtt_connect(&client, &connectParams);
	if(SUCCESS != rc) {
		ERROR("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
	}
	rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
	if(SUCCESS != rc) {
		ERROR("Unable to set Auto Reconnect to true - %d", rc);
		return;
	}

	INFO("Subscribing...");
	rc = aws_iot_mqtt_subscribe(&client, "sdkTest/sub", 11, QOS0, MQTTcallbackHandler, NULL);
	if(SUCCESS != rc) {
		ERROR("Error subscribing : %d ", rc);
	}

	char cPayload[100];
	sprintf(cPayload, "%s : %d ", "hello from SDK", (int)i);

	IoT_Publish_Message_Params paramsQOS0;
	paramsQOS0.qos = QOS0;
	paramsQOS0.payload = (void *) cPayload;

	IoT_Publish_Message_Params paramsQOS1;
	paramsQOS1.qos = QOS1;
	paramsQOS1.payload = (void *) cPayload;

	if (publishCount != 0) {
		infinitePublishFlag = false;
	}

	while((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc)
			&& (publishCount > 0 || infinitePublishFlag)) {

		//Max time the yield function will wait for read messages
		rc = aws_iot_mqtt_yield(&client, 100);
		if(NETWORK_ATTEMPTING_RECONNECT == rc){
			INFO("-->sleep");
			sleep(1);
			// If the client is attempting to reconnect we will skip the rest of the loop.
			continue;
		}

		INFO("-->sleep");
		sleep(1);
		sprintf(cPayload, "%s : %d ", "hello from SDK QOS0", (int)i++);
		paramsQOS0.payloadLen = strlen(cPayload) + 1;
		rc = aws_iot_mqtt_publish(&client, "sdkTest/sub", 11, &paramsQOS0);
		if (publishCount > 0) {
			publishCount--;
		}

		INFO("-->sleep");
		sleep(1);
		sprintf(cPayload, "%s : %d ", "hello from SDK QOS1", (int)i++);
		paramsQOS1.payloadLen = strlen(cPayload) + 1;
		do {
			rc = aws_iot_mqtt_publish(&client, "sdkTest/sub", 11, &paramsQOS1);
			if (publishCount > 0) {
				publishCount--;
			}
		} while(MQTT_REQUEST_TIMEOUT_ERROR == rc && (publishCount > 0 || infinitePublishFlag));
	}

	if(SUCCESS != rc) {
		ERROR("An error occurred in the loop.\n");
	} else {
		INFO("Publish done\n");
	}
}

void main_thread(void* p)
{
	char* ssid = xstr(WIFI_SSID);
	char* pass = xstr(WIFI_PASSWD);
	printf("wifi=%s %s\r\n", ssid, pass);
	plt_init();
	net_init();
	wifi_init(WIFI_WPA_PSK_WPA2_PSK, ssid, pass);
	ip_dhcp();
	mbedtls_platform_set_calloc_free(calloc, free);
	aws_sub_pub();
}

#ifdef _EXE_
int main(void)
{
	core_init();
	task_new("main", main_thread, 8, 6000, -1, 0);
	core_start();
	return 0;
}
#endif
