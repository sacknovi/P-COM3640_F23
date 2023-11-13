namespace edu.yu.com3640.FileProcessor.Interfaces;

public interface ISymmetricKeyGenerator
{
    /// <summary>
    /// Generates a key for symmetric encryption algorithms
    /// </summary>
    /// <returns>The shared key</returns>
    byte[] GenerateKey();

    /// <summary>
    /// Generates an Initialization Vector (IV) for symmetric encryption algorithms
    /// </summary>
    /// <returns>The initialization vector</returns>
    byte[] GenerateInitializationVector();
}
