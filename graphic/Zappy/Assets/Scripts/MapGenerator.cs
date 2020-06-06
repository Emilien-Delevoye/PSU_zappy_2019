using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class MapGenerator : MonoBehaviour
{
    public Client client;
    public GameObject plane;

    public GameObject linemate;
    public GameObject deraumere;
    public GameObject sibur;
    public GameObject mendiane;
    public GameObject phiras;
    public GameObject thystame;
    public GameObject food;

    private Vector3 spawnPos;

    private Vector3 pos;
    private Quaternion rotation;

    private int mapSizeX = 0;
    private int mapSizeY = 0;

    private float startPointX = 0.5f;
    private float startPointZ = 0.5f;

    private string receiveMessage;
    private string[] arguments;

    // Start is called before the first frame update
    void Start()
    {
        rotation.x = 0f;
        rotation.y = 0f;
        rotation.z = 0f;
        pos.x = startPointX;
        pos.z = startPointZ;

        SetUpAssetsSize();
        SetUpSizeMap();
        SetUpMap();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void SetUpAssetsSize()
    {
        food.transform.localScale = new Vector3(0.15f, 0.15f, 0.15f);
        linemate.transform.localScale = new Vector3(0.4f, 0.4f, 0.4f);

    }

    private void SetUpSizeMap()
    {
        client.SendMessageToServer("msz\n");
        //receiveMessage = client.WaitMessageFromServer();
        receiveMessage = "tmp";

        if (receiveMessage != null)
        {
            //arguments = receiveMessage.Split(' ');
            arguments = "msz 20 20\n".Split(' ');
            if (arguments[0] == "msz")
            {
                if (arguments.Length != 3)
                {
                    Debug.Log("msz: Reply missing argument.");
                    Application.Quit();
                }
                else
                {
                    mapSizeX = int.Parse(arguments[1]);
                    mapSizeY = int.Parse(arguments[2]);
                }
            }
        }
    }

    private void SetUpMap()
    {
        if (mapSizeX < mapSizeY)
        {
            for (int y = 0; y < mapSizeY; y++)
            {
                for (int x = 0; x < mapSizeX; x++)
                {
                    client.SendMessageToServer("bct " + x + " " + y + "\n");
                    Instantiate(plane, pos, rotation);
                    SetUpTile();
                    pos.x += 1f;
                }
                pos.z += 1f;
                pos.x = startPointZ;
            }
        }
        else
        {
            for (int x = 0; x < mapSizeX; x++)
            {
                for (int y = 0; y < mapSizeY; y++)
                {
                    client.SendMessageToServer("bct " + x + " " + y + "\n");
                    Instantiate(plane, pos, rotation);
                    SetUpTile();
                    pos.z += 1f;
                }
                pos.x += 1f;
                pos.z = startPointZ;
            }
        }
    }

    private void SetUpTile()
    {
        Array.Clear(arguments, 0, arguments.Length);
        //receiveMessage = client.WaitMessageFromServer();
        receiveMessage = "tmp";
        if (receiveMessage != null)
        {
            //arguments = receiveMessage.Split(' ');
            arguments = "bct 0 0 1 1 1 1 1 1 1\n".Split(' ');
            if (arguments[0] == "bct")
            {
                if (arguments.Length != 10)
                {
                    Debug.Log("bct: Reply missing argument.");
                    Application.Quit();
                }
                else
                {
                    GenerateLinemate();
                    GenerateDeraumere();
                    GenerateSibur();
                    GenerateMendiane();
                    GeneratePhiras();
                    GenerateThystame();
                }
            }
        }
    }

    public void GenerateFood()
    {
        for (int i = 0; i < int.Parse(arguments[3]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.1f;
            Instantiate(food, spawnPos, rotation);
        }
    }

    private void GenerateLinemate()
    {
        for (int i = 0; i < int.Parse(arguments[4]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.050f;
            Instantiate(linemate, spawnPos, rotation);
        }
    }

    private void GenerateDeraumere()
    {
        for (int i = 0; i < int.Parse(arguments[5]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.050f;
            Instantiate(deraumere, spawnPos, rotation);
        }
    }

    private void GenerateSibur()
    {
        for (int i = 0; i < int.Parse(arguments[6]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.050f;
            Instantiate(sibur, spawnPos, rotation);
        }
    }

    private void GenerateMendiane()
    {
        for (int i = 0; i < int.Parse(arguments[7]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.050f;
            Instantiate(mendiane, spawnPos, rotation);
        }
    }

    private void GeneratePhiras()
    {
        for (int i = 0; i < int.Parse(arguments[8]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.050f;
            Instantiate(phiras, spawnPos, rotation);
        }
    }

    private void GenerateThystame()
    {
        for (int i = 0; i < int.Parse(arguments[9]); i++)
        {
            spawnPos.x = UnityEngine.Random.Range(pos.x - 0.5f, pos.x + 0.5f);
            spawnPos.z = UnityEngine.Random.Range(pos.z - 0.5f, pos.z + 0.5f);
            spawnPos.y = 0.050f;
            Instantiate(thystame, spawnPos, rotation);
        }
    }
}
