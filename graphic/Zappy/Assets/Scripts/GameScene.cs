using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameScene : MonoBehaviour
{
    public GameObject PauseMenu;

    public Client client;

    private string receiveMessage;

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {

        receiveMessage = client.ReceiveMesageFromServer();
        if (receiveMessage != null)
        {
            Debug.Log(receiveMessage);
        }

        if (Input.GetKey(KeyCode.Escape))
        {
            //client.SendMessageToServer("PAUSE MENU");
            PauseMenu.SetActive(true);
        }
    }
}
