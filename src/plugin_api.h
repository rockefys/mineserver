/*
  Copyright (c) 2010, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _PLUGIN_API_H
#define _PLUGIN_API_H

#ifdef __cplusplus
#ifndef MINESERVER_C_API
  #define USE_HOOKS
#endif
#endif

#ifdef USE_HOOKS
#include "hook.h"
#endif

#ifdef WIN32
#define PLUGIN_API_EXPORT extern "C" __declspec(dllexport) 
#define CALLCONVERSION __cdecl
#else
#define PLUGIN_API_EXPORT extern "C"
#define CALLCONVERSION
#endif

struct plugin_pointer_struct
{
  bool  (*hasPluginVersion)(const char* name);
  float (*getPluginVersion)(const char* name);
  void  (*setPluginVersion)(const char* name, float version);
  void  (*remPluginVersion)(const char* name);

  bool  (*hasPointer)(const char* name);
  void* (*getPointer)(const char* name);
  void  (*setPointer)(const char* name, void* pointer);
  void  (*remPointer)(const char* name);

  bool  (*hasHook)(const char* hookID);
#ifdef USE_HOOKS
  Hook* (*getHook)(const char* hookID);
  void  (*setHook)(const char* hookID, Hook* hook);
#else
  void* (*getHook)(const char* hookID);
  void  (*setHook)(const char* hookID, void* hook);
#endif
  void  (*remHook)(const char* hookID);

  bool (*hasCallback)          (const char* hookID, void* function);
  void (*addCallback)          (const char* hookID, void* function);
  void (*addIdentifiedCallback)(const char* hookID, void* identifier, void* function);
  void (*remCallback)          (const char* hookID, void* function);
  bool (*doUntilTrue)          (const char* hookID, ...);
  bool (*doUntilFalse)         (const char* hookID, ...);
  void (*doAll)                (const char* hookID, ...);

  void *temp[10];
};

struct user_pointer_struct
{
  bool (*teleport)   (const char* user,double x, double y, double z);
  bool (*getPosition)(const char* user, double* x, double* y, double* z, float* yaw, float* pitch, double *stance);
  bool (*sethealth)  (const char* user,int userHealth);
  void *temp[100];
};

struct chat_pointer_struct
{
  bool (*sendmsgTo)   (const char* user,const char* msg);
  bool (*sendmsg)     (const char* msg);
  bool (*sendUserlist)(const char* user);
  void *temp[100];
};

struct logger_pointer_struct
{
  void (*log)(int type, const char* source, const char* message);
  void *temp[100];
};

struct map_pointer_struct
{
  void (*createPickupSpawn)(int x, int y, int z, int type, int count, int health, const char* user);
  bool (*setTime) (int timeValue);
  void (*getSpawn)(int* x, int* y, int* z);
  bool (*getBlock)(int x, int y, int z, unsigned char* type,unsigned char* meta);
  bool (*setBlock)(int x, int y, int z, unsigned char type,unsigned char meta);
  void (*saveWholeMap)(void);
  unsigned char* (*getMapData_block)(int x, int z);
  unsigned char* (*getMapData_meta) (int x, int z);
  unsigned char* (*getMapData_skylight)  (int x, int z);
  unsigned char* (*getMapData_blocklight)(int x, int z);
  void *temp[100];
};

struct config_pointer_struct
{
  bool (*has)(const char* name);
  int (*iData)(const char* name);
  long (*lData)(const char* name);
  float (*fData)(const char* name);
  double (*dData)(const char* name);
  const char* (*sData)(const char* name);
  bool (*bData)(const char* name);
  void *temp[100];
};

struct mineserver_pointer_struct
{
  map_pointer_struct map;
  logger_pointer_struct logger;
  chat_pointer_struct chat;
  plugin_pointer_struct plugin;
  user_pointer_struct user;
  config_pointer_struct config;

  void *temp[100];
};

// Ignore these, only used when compiling with Mineserver
#ifdef MINESERVER
void init_plugin_api(void);
extern mineserver_pointer_struct plugin_api_pointers;
#endif
#endif

