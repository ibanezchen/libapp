#!/bin/bash
#-****************************************************************************/
#-                                                                           */
#-            Copyright (c) 2013 by SOCware Inc.                             */
#-                                                                           */
#-  This software is copyrighted by and is the sole property of SOCware, Inc.*/
#-  All rights, title, ownership, or other interests in the software remain  */
#-  the property of SOCware, Inc. The source code is for FREE short-term     */
#-  evaluation, educational or non-commercial research only. Any commercial  */
#-  application may only be used in accordance with the corresponding license*/
#-  agreement. Any unauthorized use, duplication, transmission, distribution,*/
#-  or disclosure of this software is expressly forbidden.                   */
#-                                                                           */
#-  Knowledge of the source code may NOT be used to develop a similar product*/
#-                                                                           */
#-  This Copyright notice may not be removed or modified without prior       */
#-  written consent of SOCware, Inc.                                         */
#-                                                                           */
#-  SOCWare, Inc. reserves the right to modify this software                 */
#-  without notice.                                                          */
#-                                                                           */
#-             socware.help@gmail.com                                        */
#-             http://socware.net                                            */
#-                                                                           */
#-****************************************************************************/
PREFIX=${PREFIX:-../prefix/arm-none-eabi}

D=$0
D=${D%/*}
source $D/bld-lib.sh

eval $@
repo=${repo:-https://github.com/ibanezchen}

out_git hyperCOS $repo/hyperCOS-evaluate.git eva3
add_cmd hyperCOS "source bin/cfg-lib.sh && cfg_v7mTF"
add_mod hyperCOS

out_git liblinkit $repo/liblinkit.git m
add_mod liblinkit

out_git libsoc $repo/libsoc.git m
add_mod libsoc SOC=linkit
source $PREFIX/bin/cfg-linkit.sh && cfg_linkit

out_git jerryscript $repo/jerryscript.git master
add_cmd jerryscript "make -f targets/hyperc/Makefile"

out_git mbedtls $repo/mbedtls.git mbedtls-2.2.0-hyperc
add_cmd mbedtls "SOC=linkit source hcos-env.sh"
add_mod mbedtls

out_git aws-iot-device-sdk-embedded-C $repo/aws-iot-device-sdk-embedded-C.git v2.0.0-hyperc
add_cmd aws-iot-device-sdk-embedded-C "make -f platform/hyperc/Makefile"
add_cmd aws-iot-device-sdk-embedded-C "make -f platform/hyperc/Makefile install"
