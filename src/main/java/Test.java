
public class Test {

    public static void main(String[] args) {
        ILightGBMJava lib = new ILightGBMJava();
        DatesetHandle train = lib.createDatasetFromFile("/home/maksim/Downloads/LightGBM/examples/binary_classification/binary.train","max_bin=15",null);
        DatesetHandle test = lib.createDatasetFromFile("/home/maksim/Downloads/LightGBM/examples/binary_classification/binary.test","max_bin=15",train);
        System.out.println(train);
        long numData =lib.datasetGetNumData(test);
        long numFeature = lib.datasetGetNumFeature(test);
        System.out.println(numData+" feature: " + numFeature+ " free result:");


        Booster booster =lib.createBoosterFromModelFile("/home/maksim/Downloads/LightGBM/examples/binary_classification/LightGBM_model.txt");


        int resul = lib.datasetFree(test);
        System.out.println(lib.getLastError());
    }
}
