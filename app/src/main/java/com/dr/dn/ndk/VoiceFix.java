package com.dr.dn.ndk;

/**
 * 项目名称：DN_NDKApp
 * 类描述：
 * 创建人：yuliyan
 * 创建时间：2019-04-23 01:34
 * 修改人：yuliyan
 * 修改时间：2019-04-23 01:34
 * 修改备注：
 */
public class VoiceFix {
    public static int MODE_NORMAL = 0;
    public static int MODE_LUOLI = 1;
    public static int MODE_AUNCALL = 2;
    public static int MODE_JINGSONG = 3;
    public static int MODE_GAOXIAO = 4;
    public static int MODE_LINGHUNCHUQIAO = 5;
    static {
        System.loadLibrary("native-lib");
    }
    
    public static native void fix(int model, String voicePath);
}
