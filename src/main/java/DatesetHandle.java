import java.io.Closeable;


public class DatesetHandle{
    private long nativePtr;

    public DatesetHandle(long nativePtr) {
        this.nativePtr = nativePtr;
    }

    public long getNativePtr() {
        return nativePtr;
    }
}
