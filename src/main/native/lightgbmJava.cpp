#include <vector>
#include <functional>
#include "c_api.h"
#include "ILightGBMJava.h"
#include "handle.h"


JNIEXPORT jobject JNICALL Java_ILightGBMJava_createDatasetFromFile
  (JNIEnv * env, jobject object, jstring jFileName, jstring jParams, jobject jDataHandler){
    const char *fileName = env->GetStringUTFChars(jFileName,0);
    const char *params = env->GetStringUTFChars(jParams,0);
    
    DatesetHandle out;
    DatesetHandle* dh;
    
    //Get native datahandler if it exist
    if(!(env->IsSameObject(jDataHandler,NULL))){
        *dh = getHandle<DatesetHandle>(env,jDataHandler);
    }
    else dh=NULL;
    
    
    int result = LGBM_DatasetCreateFromFile(fileName,params,dh,&out);

    jobject jResult=NULL;
    if(result == 0){
        jclass clsDataHandler = env->FindClass("DatesetHandle");//TODO move class name to constants in h
        jmethodID constructorDataHandler = env->GetMethodID(clsDataHandler,"<init>","(J)V");
        jlong jOut = (jlong) out;
        jResult = env->NewObject(clsDataHandler,constructorDataHandler,jOut);
    }
    
    
    env->ReleaseStringUTFChars(jFileName,fileName);
    env->ReleaseStringUTFChars(jParams,params);

    return jResult;
  }

/*
 * Class:     ILightGBMJava
 * Method:    getLastError
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ILightGBMJava_getLastError
  (JNIEnv *env, jobject obj){
      jstring result;
      const char* errorStr = LGBM_GetLastError();
      result = env->NewStringUTF(errorStr);
      free((char*)errorStr);
      return result;
      
  }

/*
 * Class:     ILightGBMJava
 * Method:    datasetFree
 * Signature: (LDatesetHandle;)I
 */
JNIEXPORT jint JNICALL Java_ILightGBMJava_datasetFree
  (JNIEnv * env, jobject obj, jobject jDataHandler){
      DatesetHandle handle = getHandle<DatesetHandle>(env,jDataHandler);
      return LGBM_DatasetFree(handle);
    }

/*
 * Class:     ILightGBMJava
 * Method:    datasetSaveBinary
 * Signature: (LDatesetHandle;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_ILightGBMJava_datasetSaveBinary
  (JNIEnv * env, jobject obj, jobject jDataHandle, jstring jFileName){
      DatesetHandle handle = getHandle<DatesetHandle>(env,jDataHandle);
      const char *fileName = env->GetStringUTFChars(jFileName,0);
      
      int result = LGBM_DatasetSaveBinary(handle,fileName);
      
      env->ReleaseStringUTFChars(jFileName,fileName);
      
      return result;
  }

/*
 * Class:     ILightGBMJava
 * Method:    datasetGetNumData
 * Signature: (LDatesetHandle;)J
 */
JNIEXPORT jlong JNICALL Java_ILightGBMJava_datasetGetNumData
  (JNIEnv * env, jobject obj, jobject jDataHandle){
      DatesetHandle handle = getHandle<DatesetHandle>(env,jDataHandle);
      int64_t out;
      
      int result = LGBM_DatasetGetNumData(handle,&out);
      
      if(result == 0){
          return out;
      }else{
          return -1;
      }
  }

/*
 * Class:     ILightGBMJava
 * Method:    datasetGetNumFeature
 * Signature: (LDatesetHandle;)J
 */
JNIEXPORT jlong JNICALL Java_ILightGBMJava_datasetGetNumFeature
  (JNIEnv *env, jobject obj, jobject jDataHandle){
       DatesetHandle handle = getHandle<DatesetHandle>(env,jDataHandle);
      int64_t out;
      
      int result = LGBM_DatasetGetNumFeature(handle,&out);
      
      if(result == 0){
          return out;
      }else{
          return -1;
      }
  }
  
JNIEXPORT jobject JNICALL Java_ILightGBMJava_createBooster
  (JNIEnv * env, jobject obj, jobject jHandler, jstring jParams){
      BoosterHandle booster;
      DatesetHandle handle;
      const char* params;
      jobject jResult;
      
      handle = getHandle<DatesetHandle>(env,jHandler);
      params = env->GetStringUTFChars(jParams,0);
      
      int result = LGBM_BoosterCreate(handle,params,&booster);
      
      jResult = NULL;
      if(result == 0){
          jclass clsBooster = env->FindClass("Booster");//TODO move class name to constants in h
          jmethodID constructorBooster = env->GetMethodID(clsBooster,"<init>","(J)V");
          jlong jOut = (jlong) booster;
          jResult = env->NewObject(clsBooster,constructorBooster,jOut);
        }
      
      
      env->ReleaseStringUTFChars(jParams,params);
      
      return jResult;
  }

/*
 * Class:     ILightGBMJava
 * Method:    createBoosterFromModelFile
 * Signature: (Ljava/lang/String;J)LBooster;
 */
JNIEXPORT jobject JNICALL Java_ILightGBMJava_createBoosterFromModelFile
  (JNIEnv * env, jobject obj, jstring jFileName){
    const char *fileName = env->GetStringUTFChars(jFileName,0);
    
    BoosterHandle out;
    int64_t outNumbIter;
    
    
    
    int result = LGBM_BoosterCreateFromModelfile(fileName,&outNumbIter, &out);
    jobject jResult=NULL;
    if(result == 0){
        jclass clsBooster = env->FindClass("Booster");//TODO move class name to constants in h
        jmethodID constructorBooster = env->GetMethodID(clsBooster,"<init>","(J)V");
        jlong jOut = (jlong) out;
        jResult = env->NewObject(clsBooster,constructorBooster,jOut);
        
        jfieldID jIterField = env->GetFieldID(clsBooster, "numbIteration", "J");
        env->SetLongField(jResult, jIterField, (jlong) outNumbIter);
    }
    
    
    env->ReleaseStringUTFChars(jFileName,fileName);

    return jResult;
      
      
  }

/*
 * Class:     ILightGBMJava
 * Method:    predictBoosterForMat
 * Signature: (LBooster;[FIIZJ)[F
 */
JNIEXPORT jfloatArray JNICALL Java_ILightGBMJava_predictBoosterForMat
  (JNIEnv * env,
    jobject obj,
    jobject jBooster,
    jfloatArray jdata,
    jint jNrow,
    jint jNcol,
    jboolean jIsRowMajor,
    jint predictType,
    jlong jNumIteration,
    jint jMemSize)
    {
      BoosterHandle booster = getHandle<BoosterHandle>(env,jBooster);
      float* data = env->GetFloatArrayElements(jdata,0);
      
      int64_t outLen;
      int memSize = (int)jMemSize;
      float* outResult = new float[memSize];
      int result = LGBM_BoosterPredictForMat(booster,data,C_API_DTYPE_FLOAT32,(int) jNrow, (int)jNcol,
                                    (int)jIsRowMajor,(int) predictType,(int64_t) jNumIteration, &outLen,outResult);
                                
      jfloatArray jResult = env->NewFloatArray(outLen);
      if(result==0){
        env->SetFloatArrayRegion(jResult,0,outLen,outResult);
      }
                                    
      
      env->ReleaseFloatArrayElements(jdata,data,0);
      
      
      
      return jResult;
      }
