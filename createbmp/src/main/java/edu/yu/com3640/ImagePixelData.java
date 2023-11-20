package edu.yu.com3640;

public interface ImagePixelData {

    void addRow(Pixel[] row);

    int rows();

    int cols();

    Pixel getPixel(int row, int col);

    void setPixel(int row, int col, Pixel pixel);

}