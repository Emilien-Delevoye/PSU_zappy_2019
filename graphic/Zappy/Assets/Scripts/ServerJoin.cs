using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using UnityEngine.Networking;
using UnityEngine.UI;
using System.Threading;
using System;
using TMPro;
using System.Text;
using UnityEngine.SceneManagement;

public class ServerJoin : MonoBehaviour
{

    public TMP_InputField IpField;
    public TMP_InputField PortField;

    private Thread clientReceiveThread;
    private TcpClient socketConnection;

    private string ip;
    private string port;

    // Start is called before the first frame update
    void Start()
    {
        ConnectToServer();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void UpdateIp()
    {
        ip = IpField.text;

        Debug.Log(ip);
    }

    public void UpdatePort()
    {
        port = PortField.text;

        Debug.Log(port);
    }

    private void ConnectToServer()
    {
        socketConnection = new TcpClient(ip, int.Parse(port));

    }

    public void PlayGame()
    {
        ConnectToServer();
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    //private void ConnectToTcpServer()
    //{
    //    try
    //    {
    //        clientReceiveThread = new Thread(new ThreadStart(ListenForData));
    //        clientReceiveThread.IsBackground = true;
    //        clientReceiveThread.Start();
    //    }
    //    catch (Exception e)
    //    {
    //        Debug.Log("On client connect exception " + e);
    //    }
    //}

    //private void ListenForData()
    //{
    //    try
    //    {
    //        socketConnection = new TcpClient("192.168.1.63", 4242);
    //        Byte[] bytes = new Byte[1024];
    //        while (true)
    //        {
    //            // Get a stream object for reading 				
    //            using (NetworkStream stream = socketConnection.GetStream())
    //            {
    //                int length;
    //                // Read incomming stream into byte arrary. 					
    //                while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
    //                {
    //                    var incommingData = new byte[length];
    //                    Array.Copy(bytes, 0, incommingData, 0, length);
    //                    // Convert byte array to string message. 						
    //                    string serverMessage = Encoding.ASCII.GetString(incommingData);
    //                    Debug.Log("server message received as: " + serverMessage);
    //                }
    //            }
    //        }
    //    }
    //    catch (SocketException socketException)
    //    {
    //        Debug.Log("Socket exception: " + socketException);
    //    }
    //}
    ///// <summary> 	
    ///// Send message to server using socket connection. 	
    ///// </summary> 	
    //private void SendMessage()
    //{
    //    if (socketConnection == null)
    //    {
    //        return;
    //    }
    //    try
    //    {
    //        // Get a stream object for writing. 			
    //        NetworkStream stream = socketConnection.GetStream();
    //        if (stream.CanWrite)
    //        {
    //            string clientMessage = "This is a message from one of your clients.";
    //            // Convert string message to byte array.                 
    //            byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage);
    //            // Write byte array to socketConnection stream.                 
    //            stream.Write(clientMessageAsByteArray, 0, clientMessageAsByteArray.Length);
    //            Debug.Log("Client sent his message - should be received by server");
    //        }
    //    }
    //    catch (SocketException socketException)
    //    {
    //        Debug.Log("Socket exception: " + socketException);
    //    }
    //}
}
