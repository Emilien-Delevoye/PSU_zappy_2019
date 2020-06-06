using UnityEngine;
using System.Net.Sockets;
using System;
using System.Threading.Tasks;


public class Client : MonoBehaviour
{
    static private TcpClient client;

    static private NetworkStream stream;
    
    private string responseData = null;
    private Byte[] sendBytes;
    private Byte[] receiver;

    public Client()
    {

    }

    public void ConnectToServer(string ip, int port)
    {
        try
        {
            client = new TcpClient();
            client.ConnectAsync(ip, port);
        }
        catch (SocketException)
        {
            Debug.Log("Can't connect to the server.");
        }
    }

    public void DisconectFromServer()
    {
        stream.Close();
        client.Close();
    }
    
    public bool Connected()
    {
        if (client.Connected == true)
        {
            stream = client.GetStream();
            return true;
        }
        else
        {
            return false;
        }
    }

    public void SendMessageToServer(string message)
    {
        if (stream.CanWrite)
        {
            sendBytes = System.Text.Encoding.ASCII.GetBytes(message);
            stream.Write(sendBytes, 0, sendBytes.Length);
            Debug.Log("Sent: " + message);
        } else
        {
            Debug.Log("Stream can't write.");

        }
    }

    public string ReceiveMesageFromServer()
    {
        if (stream.CanRead && stream.DataAvailable)
        {
            receiver = new Byte[2048];
            responseData = String.Empty;

            Int32 bytes = stream.Read(receiver, 0, receiver.Length);
            responseData = System.Text.Encoding.ASCII.GetString(receiver, 0, bytes);
            Debug.Log("Receive: " + responseData);
            return responseData;
        }
        return null;
    }

    public string WaitMessageFromServer()
    {
        if (stream.CanRead)
        {
            receiver = new Byte[2048];
            responseData = String.Empty;

            Int32 bytes = stream.Read(receiver, 0, receiver.Length);
            responseData = System.Text.Encoding.ASCII.GetString(receiver, 0, bytes);
            Debug.Log("Receive: " + responseData);
            return responseData;
        }
        return null;
    }
}
