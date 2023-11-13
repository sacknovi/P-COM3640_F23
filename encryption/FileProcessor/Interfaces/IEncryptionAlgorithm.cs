namespace edu.yu.com3640.FileProcessor.Interfaces;

/// <summary>
/// Interface for encryption algorithms
/// </summary>
public interface IEncryptionAlgorithm
{
    /// <summary>
    /// Encrypts the given data with the given key
    /// </summary>
    /// <param name="data"></param>
    /// <returns>The encrypted byte array</returns>
    byte[] Encrypt(byte[] data);

    /// <summary>
    /// Decrypts the given data with the given key
    /// </summary>
    /// <param name="data"></param>
    /// <returns>The decrypted byte array</returns>
    byte[] Decrypt(byte[] data);
}

