package edu.yu.com3640.Impl;

import java.io.IOException;

import edu.yu.com3640.ImagePixelData;
import edu.yu.com3640.PixelDataLoader;

public class RgbPixelDataTextFile implements PixelDataLoader {

    private final String filePath;

    public RgbPixelDataTextFile(String filePath) {
        this.filePath = filePath;
    }

    public ImagePixelData loadPixelData() throws IOException {
        throw new UnsupportedOperationException("Not yet implemented " + filePath);
    }

}
