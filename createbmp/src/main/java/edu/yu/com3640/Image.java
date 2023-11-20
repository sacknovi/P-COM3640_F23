package edu.yu.com3640;

import java.io.IOException;

public interface Image {

    /**
     * Returns the width of the image in pixels
     * 
     * @return the width of the image in pixels
     */
    int getWidth();

    /**
     * Returns the height of the image in pixels
     * 
     * @return the height of the image in pixels
     */
    int getHeight();

    /**
     * Saves the image to a file at the given file path
     * 
     * @param filePath
     * @throws IOException
     */
    void saveToFile(String filePath) throws IOException;

    /**
     * Flips the image horizontally
     */
    void flipHorizontal();

    /**
     * Flips the image vertically
     */
    void flipVertical();

    /**
     * Converts the image to grayscale
     */
    void convertToGrayScale();
}
