package edu.yu.com3640;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class App {
    private static final Logger logger = LogManager.getLogger(App.class);

    public static void main(String[] args) {
        logger.info("Application starting");

        if (args.length < 1) {
            logger.fatal("No file path provided. Exiting application.");
            System.exit(1);
        }

        String filePath = args[0];

        Image image = ImageFactory.create24BitBMPImage(filePath);
        processImage(image, "24");

        image = ImageFactory.create32BitBMPImage(filePath);
        processImage(image, "32");

        image = ImageFactory.create16BitBMPImage(filePath);
        processImage(image, "16");

        image = ImageFactory.create8BitBMPImage(filePath);
        processImage(image, "8");

        logger.info("Application exiting");
    }

    private static void processImage(Image image, String bitDepth) {
        logger.info("Processing image with bit depth " + bitDepth);

        logger.info("Image width: " + image.getWidth());
        logger.info("Image height: " + image.getHeight());

        logger.info("Saving image to file");
        try {
            image.saveToFile(bitDepth + ".bmp");
        } catch (Exception e) {
            logger.error("Failed to save image to file", e);
        }

        logger.info("Flipping image horizontally");
        image.flipHorizontal();

        logger.info("Saving image to file");
        try {
            image.saveToFile(bitDepth + "-H.bmp");
        } catch (Exception e) {
            logger.error("Failed to save image to file", e);
        }

        logger.info("Flipping image vertically");
        image.flipVertical();

        logger.info("Saving image to file");
        try {
            image.saveToFile(bitDepth + "-V.bmp");
        } catch (Exception e) {
            logger.error("Failed to save image to file", e);
        }

        logger.info("Converting image to grayscale");
        image.convertToGrayScale();

        logger.info("Saving image to file");
        try {
            image.saveToFile(bitDepth + "-G.bmp");
        } catch (Exception e) {
            logger.error("Failed to save image to file", e);
        }
    }
}
