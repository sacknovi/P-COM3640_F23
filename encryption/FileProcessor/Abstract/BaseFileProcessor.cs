namespace edu.yu.com3640.FileProcessor.Abstract;

public abstract class BaseFileProcessor
{
    protected abstract byte[] ProcessData(byte[] data);

    /// <summary>
    /// Processes the given file
    /// <param name="inputFilePath">The path to the input file</param>
    /// <param name="outputFilePath">The path to the output file</param>
    /// <returns></returns>
    /// </summary>
    public void Process(string inputFilePath, string outputFilePath)
    {
        // Read file and process data
        byte[] data = File.ReadAllBytes(inputFilePath);

        // call the abstract method to process the data
        byte[] processedData = ProcessData(data);

        // write the processed data to the output file
        File.WriteAllBytes(outputFilePath, processedData);
    }
}
