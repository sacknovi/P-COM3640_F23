package edu.yu.com3640.Impl;

import java.util.ArrayList;

import edu.yu.com3640.ImagePixelData;
import edu.yu.com3640.Pixel;

public class PixelData implements ImagePixelData {

    public final int columns;
    public final ArrayList<Pixel[]> pixelData;

    private PixelData(int columns) {
        this.columns = columns;
        this.pixelData = new ArrayList<>();
    }
    
    @Override
    public void addRow(Pixel[] row) {
        if (row.length != this.columns) {
            throw new IllegalArgumentException("Row length must match number of columns");
        }   
        this.pixelData.add(row);
    }

    @Override
    public int rows() {
        return this.pixelData.size();
    }

    @Override
    public int cols() {
        return this.columns;
    }

    @Override
    public Pixel getPixel(int row, int col) {
        return this.pixelData.get(row)[col];
    }

    @Override
    public void setPixel(int row, int col, Pixel pixel) {
        this.pixelData.get(row)[col] = pixel;
    }




}
