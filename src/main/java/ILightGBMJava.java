
public class ILightGBMJava{

    public enum PREDICT_TYPE{
        PREDICT_NORMAL, PREDICT_RAW_SCORE, PREDICT_LEAF_INDEX
    }

    static {
        System.loadLibrary("LightGBMJni");
    }

    /**
     * @return out from of documentation
     */
    public native DatesetHandle createDatasetFromFile(String filename,
                                                      String parameters,
                                                      DatesetHandle handle);

    public native String getLastError();

    public native int datasetFree(DatesetHandle handle);

    public native int datasetSaveBinary(DatesetHandle handle, String filename);

    public native long datasetGetNumData(DatesetHandle handle);

    public native long datasetGetNumFeature(DatesetHandle handle);

    public native Booster createBooster(DatesetHandle trainData,String parameters);

    public native Booster createBoosterFromModelFile(String fileName);

    public native float[] predictBoosterForMat(Booster booster,
                                               float[] data,
                                               int rowsNumb,
                                               int colNumb,
                                               boolean isRawMajor,
                                               PREDICT_TYPE predict_type,
                                               long numbIteration);



}
