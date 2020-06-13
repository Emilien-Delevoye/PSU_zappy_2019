using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.Threading.Tasks;

public class GameScene : MonoBehaviour
{
    public GameObject PauseMenu;

    public Client client;
    public GameObject plane;

    public GameObject food;
    public GameObject linemate;
    public GameObject deraumere;
    public GameObject sibur;
    public GameObject mendiane;
    public GameObject phiras;
    public GameObject thystame;

    public GameObject character;

    private Vector3 spawnPos;

    private Vector3 mapPos;
    private Quaternion rotation;

    private int mapSizeX = 0;
    private int mapSizeY = 0;

    private float startPointX = 0.5f;
    private float startPointZ = 0.5f;

    private string receiveMessage;
    private string[] arguments;

    private LinkedList<string> teams;

    public class Character
    {
        public Character(GameObject gameObject, int number, int posX, int posY, int orientation, int level, string teamName)
        {
            _gameObject = gameObject;
            _number = number;
            _posX = posX;
            _posY = posY;
            _posToMoveX = posX;
            _posToMoveY = posY;
            _orientation = orientation;
            _level = level;
            _teamName = teamName;
            _animator = _gameObject.gameObject.GetComponent<Animator>();
            _gameObject.transform.position = new Vector3(UnityEngine.Random.Range(posX + 0.2f, posX + 0.8f), 0, UnityEngine.Random.Range(posY + 0.2f, posY + 0.8f));
            if (orientation == 1)
                _gameObject.transform.eulerAngles = new Vector3(0f, 0f, 0f);
            else if (orientation == 2)
                _gameObject.transform.eulerAngles = new Vector3(0f, 90f, 0f);
            else if (orientation == 3)
                _gameObject.transform.eulerAngles = new Vector3(0f, 180f, 0f);
            else if (orientation == 4)
                _gameObject.transform.eulerAngles = new Vector3(0f, 270f, 0f);
        }

        public void SetPosition(int posX, int posY)
        {
            _posX = posX;
            _posY = posY;
            _gameObject.transform.position = new Vector3(_posX, 0, _posY);
        }

        public void SetPointToMove(int posX, int posY)
        {
            _posToMoveX = posX;
            _posToMoveY = posY;
        }

        public bool NeedToMove()
        {
            if (_posToMoveX == _posX && _posToMoveY == _posY)
            {
                _animator.SetInteger("run", 0);
                return false;
            }
            _animator.SetInteger("run", 1);
            return true;
        }

        public void Move()
        {
            if (_posToMoveX/2 >= _gameObject.transform.position.x - 0.5f && _posToMoveX/2 <= _gameObject.transform.position.x + 0.5f)
            {
                _posX = _posToMoveX;
            }
            if (_posToMoveY/2 >= _gameObject.transform.position.z - 0.5f && _posToMoveY/2 <= _gameObject.transform.position.z + 0.5f)
            {
                _posY = _posToMoveY;
            }
            if (_posToMoveX > _posX)
                _gameObject.transform.Translate(1f * Time.deltaTime, 0, 0, Space.World);
            if (_posToMoveY > _posY)
                _gameObject.transform.Translate(0, 0, 1f * Time.deltaTime, Space.World);
            if (_posToMoveX < _posX)
                _gameObject.transform.Translate(-1f * Time.deltaTime, 0, 0, Space.World);
            if (_posToMoveY < _posY)
                _gameObject.transform.Translate(0, 0, -1f * Time.deltaTime, Space.World);

        }

        public void SetOrientation(int orientation)
        {
            if (orientation == 1)
                _gameObject.transform.eulerAngles = new Vector3(0f, 0f, 0f);
            else if (orientation == 2)
                _gameObject.transform.eulerAngles = new Vector3(0f, 90f, 0f);
            else if (orientation == 3)
                _gameObject.transform.eulerAngles = new Vector3(0f, 180f, 0f);
            else if (orientation == 4)
                _gameObject.transform.eulerAngles = new Vector3(0f, 270f, 0f);
        }

        private GameObject _gameObject;
        private Animator _animator;
        private int _number;
        private int _posX;
        private int _posY;
        private int _posToMoveX;
        private int _posToMoveY;
        private int _orientation;
        private int _level;
        private string _teamName;
    };
    private Dictionary<int, Character> characters;

    public class Tile
    {
        public Tile(int posX, int posY, int numberFood, int numberLinemate, int numberDeraumere, int numberSibur, int numberMendiane, int numberPhiras, int numberThystame,
            Vector3 mapPos, GameObject food, GameObject linemate, GameObject deraumere, GameObject sibur, GameObject mendiane, GameObject phiras, GameObject thystame)
        {
            _foodList = new LinkedList<GameObject>();
            _linemateList = new LinkedList<GameObject>();
            _deraumereList = new LinkedList<GameObject>();
            _siburList = new LinkedList<GameObject>();
            _mendianeList = new LinkedList<GameObject>();
            _phirasList = new LinkedList<GameObject>();
            _thystameList = new LinkedList<GameObject>();

            for (int i = 0; i < numberFood; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.1f;
                _foodList.AddLast(Instantiate(food, _spawnPos, _rotation));
            }

            for (int i = 0; i < numberLinemate; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.050f;
                _linemateList.AddLast(Instantiate(linemate, _spawnPos, _rotation));
            }

            for (int i = 0; i < numberDeraumere; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.050f;
                _deraumereList.AddLast(Instantiate(deraumere, _spawnPos, _rotation));
            }

            for (int i = 0; i < numberSibur; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.050f;
                _siburList.AddLast(Instantiate(sibur, _spawnPos, _rotation));
            }

            for (int i = 0; i < numberMendiane; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.050f;
               _mendianeList.AddLast(Instantiate(mendiane, _spawnPos, _rotation));
            }

            for (int i = 0; i < numberPhiras; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.050f;
                _phirasList.AddLast(Instantiate(phiras, _spawnPos, _rotation));
            }

            for (int i = 0; i < numberThystame; i++)
            {
                _spawnPos.x = UnityEngine.Random.Range(mapPos.x - 0.5f, mapPos.x + 0.5f);
                _spawnPos.z = UnityEngine.Random.Range(mapPos.z - 0.5f, mapPos.z + 0.5f);
                _spawnPos.y = 0.050f;

               _thystameList.AddLast(Instantiate(thystame, _spawnPos, _rotation));
            }
        }

        private LinkedList<GameObject> _foodList;
        private LinkedList<GameObject> _linemateList;
        private LinkedList<GameObject> _deraumereList;
        private LinkedList<GameObject> _siburList;
        private LinkedList<GameObject> _mendianeList;
        private LinkedList<GameObject> _phirasList;
        private LinkedList<GameObject> _thystameList;
        private int _posX;
        private int _posY;
        private Vector3 _spawnPos;
        private Quaternion _rotation;

    }
    private LinkedList<Tile> map;

    static int tmp = 0;

    // Start is called before the first frame update
    void Start()
    {
        rotation.x = 0f;
        rotation.y = 0f;
        rotation.z = 0f;
        mapPos.x = startPointX;
        mapPos.z = startPointZ;

        characters = new Dictionary<int, Character>();
        map = new LinkedList<Tile>();

        SetUpAssetsSize();
        SetUpSizeMap();
        SetUpMap();
        GetTeamsName();
    }

    // Update is called once per frame
    void Update()
    {
        ReceiveMessageFromServer();
        foreach (KeyValuePair<int, Character> kvp in characters)
        {
            if (characters[kvp.Key].NeedToMove())
            {
                characters[kvp.Key].Move();
            }
        }

        if (Input.GetKey(KeyCode.Escape))
        {
            PauseMenu.SetActive(true);
        }
    }

    public void ReceiveMessageFromServer()
    {
        receiveMessage = client.ReceiveMesageFromServer();
        if (tmp == 0)
            receiveMessage = "pnw 0 0 0 2 3 Team1\n";
        else if (tmp == 150)
            receiveMessage = "ppo 0 5 0 2\n";
        else if (tmp == 300)
            receiveMessage = "ppo 0 0 0 4\n";
        else
            receiveMessage = null;
        ++tmp;
        if (receiveMessage != null)
        {
            Array.Clear(arguments, 0, arguments.Length);
            arguments = receiveMessage.Split(' ');
            if (arguments[0] == "pnw")
            {
                InstantiateNewPlayer();
            } else if (arguments[0] == "ppo")
            {
                SetPointToMovePlayer();
            }

        }
    }

    public void SetPointToMovePlayer()
    {
        if (arguments.Length >= 5)
        {
            characters[int.Parse(arguments[1])].SetPointToMove(int.Parse(arguments[2]), int.Parse(arguments[3]));
            characters[int.Parse(arguments[1])].SetOrientation(int.Parse(arguments[4]));
        } else
        {
            Debug.Log("ppo: Reply missing argument.");
        }
    }

    public void InstantiateNewPlayer()
    {
        if (arguments.Length >= 7)
        {
            characters.Add(int.Parse(arguments[1]), new Character(Instantiate(character), int.Parse(arguments[1]), int.Parse(arguments[2]), int.Parse(arguments[3]), int.Parse(arguments[4]), int.Parse(arguments[5]), arguments[6]));
        } else
        {
            Debug.Log("pnw: Reply missing argument.");
        }
    }


    public void GetTeamsName()
    {
        teams = new LinkedList<string>();
        client.SendMessageToServer("tna\n");
        //receiveMessage = client.WaitMessageFromServer();
        receiveMessage = "tna Team1 Team2 Team3 Team4 Team5";

        if (receiveMessage != null)
        {
            arguments = receiveMessage.Split(' ');
            
            if (arguments[0] == "tna")
            {
                for (int i = 0; i < arguments.Length; i++)
                    teams.AddLast(arguments[i]);
            }
        }

    }

    private void SetUpAssetsSize()
    {
        food.transform.localScale = new Vector3(0.15f, 0.15f, 0.15f);
        linemate.transform.localScale = new Vector3(0.4f, 0.4f, 0.4f);
    }

    private void SetUpSizeMap()
    {
        client.SendMessageToServer("msz\n");
        receiveMessage = client.WaitMessageFromServer();

        if (receiveMessage != null)
        {
            arguments = receiveMessage.Split(' ');
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
                    Instantiate(plane, mapPos, rotation);
                    SetUpTile(x, y);
                    mapPos.x += 1f;
                }
                mapPos.z += 1f;
                mapPos.x = startPointZ;
            }
        }
        else
        {
            for (int x = 0; x < mapSizeX; x++)
            {
                for (int y = 0; y < mapSizeY; y++)
                {
                    client.SendMessageToServer("bct " + x + " " + y + "\n");
                    Instantiate(plane, mapPos, rotation);
                    SetUpTile(x, y);
                    mapPos.z += 1f;
                }
                mapPos.x += 1f;
                mapPos.z = startPointZ;
            }
        }
    }

    private void SetUpTile(int x, int y)
    {
        Array.Clear(arguments, 0, arguments.Length);
        receiveMessage = client.WaitMessageFromServer();

        if (receiveMessage != null)
        {
            arguments = receiveMessage.Split(' ');
            if (arguments[0] == "bct")
            {
                if (arguments.Length != 10)
                {
                    Debug.Log("bct: Reply missing argument.");
                    Application.Quit();
                }
                else
                {
                    map.AddLast(new Tile(x, y, int.Parse(arguments[3]), int.Parse(arguments[4]), int.Parse(arguments[5]), int.Parse(arguments[6]), int.Parse(arguments[7]), int.Parse(arguments[8]),
                        int.Parse(arguments[9]), mapPos, food, linemate, deraumere, sibur, mendiane, phiras, thystame));
                }
            }
        }
    }
}
