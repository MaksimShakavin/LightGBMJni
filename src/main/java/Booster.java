
public class Booster {
    private long nativePtr;
    private long numbIteration;

    public Booster(long nativePtr) {
        this.nativePtr = nativePtr;
    }

    public long getNativePtr() {
        return nativePtr;
    }

    public long getNumbIteration() {
        return numbIteration;
    }
}
