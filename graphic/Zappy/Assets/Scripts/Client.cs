using UnityEngine;
using System.Net.Sockets;

public class Client : MonoBehaviour
{
    static private TcpClient client;

    //Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

    public Client()
    {

    }

    public bool ConnectToServer(string ip, int port)
    {
        try
        {
            client = new TcpClient();
            client.ConnectAsync(ip, port);
            if (client.Connected)
                return true;
            return false;
        }
        catch (SocketException)
        {
            Debug.Log("Can't connect to the server.");
            return false;
        }
    }

    public void DisconectFromServer()
    {
        client.Close();
    }
    
    public bool Connected()
    {
        return client.Connected;
    }

}
