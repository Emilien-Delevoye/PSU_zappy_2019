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
        public Character(GameObject gameObject, int number, int posX, int posY, int orientation, int level, string teamName, int mapX, int mapY)
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
            _mapX = mapX;
            _mapY = mapY;
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
            if (_gameObject.transform.position.x - 0.25f >=_posToMoveX && _gameObject.transform.position.x - 0.75 <= _posToMoveX)
            {
                _posX = _posToMoveX;
            }
            if (_gameObject.transform.position.z - 0.25f >= _posToMoveY && _gameObject.transform.position.z - 0.75 <= _posToMoveY)
            {
                _posY = _posToMoveY;
            }


            if (_posToMoveX > _posX && _posToMoveX == _mapX - 1) /// Gauche de la map TP droite
            {
                _gameObject.transform.Translate(-1f * Time.deltaTime, 0, 0, Space.World);
                if (_gameObject.transform.position.x < 0f)
                    _gameObject.transform.position = new Vector3(_mapX, 0, _posY);
            } else if (_posToMoveX < _posX && _posToMoveX == 0 && _posX == _mapX - 1) /// Droite de la map TP gauche
            {
                _gameObject.transform.Translate(1f * Time.deltaTime, 0, 0, Space.World);
                if (_gameObject.transform.position.x > _mapX)
                    _gameObject.transform.position = new Vector3(0, 0, _posY);
            }
            else if (_posToMoveY > _posY && _posToMoveY == _mapY - 1) /// Bas de la map TP haut
            {
                _gameObject.transform.Translate(0, 0, -1f * Time.deltaTime, Space.World);
                if (_gameObject.transform.position.z < 0f)
                    _gameObject.transform.position = new Vector3(_posX, 0, _mapY);
            } else if (_posToMoveY < _posY && _posToMoveY == 0 && _posY == _mapY - 1) /// Haut de la map TP bas
            {
                _gameObject.transform.Translate(0, 0, 1f * Time.deltaTime, Space.World);
                if (_gameObject.transform.position.z > _mapY)
                    _gameObject.transform.position = new Vector3(_posX, 0, 0);
            }
            else
            {
                if (_posToMoveX > _posX)
                    _gameObject.transform.Translate(1f * Time.deltaTime, 0, 0, Space.World);
                if (_posToMoveY > _posY)
                    _gameObject.transform.Translate(0, 0, 1f * Time.deltaTime, Space.World);
                if (_posToMoveX < _posX)
                    _gameObject.transform.Translate(-1f * Time.deltaTime, 0, 0, Space.World);
                if (_posToMoveY < _posY)
                    _gameObject.transform.Translate(0, 0, -1f * Time.deltaTime, Space.World);
            }
            

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
        private int _mapX;
        private int _mapY;
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
            _rotation = new Quaternion(0f, 0f, 0f, 0f);

            _posX = posX;
            _posY = posY;

             _food = food;
            _linemate = linemate;
            _deraumere = deraumere;
            _sibur = sibur;
            _mendiane = mendiane;
            _phiras = phiras;
            _thystame = thystame;

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

        public bool GoodTileSelected(int x, int y)
        {
            if (_posX == x && _posY == y)
                return true;
            return false;
        }

        public void UpdateTile(int numberFood, int numberLinemate, int numberDeraumere, int numberSibur, int numberMendiane, int numberPhiras, int numberThystame)
        {
            int diff = 0;
            if (_foodList.Count < numberFood)
            {
                diff = numberFood - _foodList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.1f;
                    _foodList.AddLast(Instantiate(_food, _spawnPos, _rotation));
                }
            }
            else if (_foodList.Count > numberFood)
            {
                diff = _foodList.Count - numberFood;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_foodList.Last.Value);
                    _foodList.RemoveLast();
                    Debug.Log("Food Deleted");
                }
            }
            if (_linemateList.Count < numberLinemate)
            {
                diff = numberLinemate - _linemateList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.050f;
                    _foodList.AddLast(Instantiate(_linemate, _spawnPos, _rotation));
                }
            } else if (_linemateList.Count > numberLinemate) 
            {
                diff = _linemateList.Count - numberLinemate;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_linemateList.Last.Value);
                    _linemateList.RemoveLast();
                    Debug.Log("Linemate Deleted");
                }
            }
            if (_deraumereList.Count < numberDeraumere)
            {
                diff = numberDeraumere - _deraumereList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.050f;
                    _foodList.AddLast(Instantiate(_deraumere, _spawnPos, _rotation));
                }
            } else if (_deraumereList.Count > numberDeraumere)
            {
                diff = _deraumereList.Count - numberDeraumere;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_deraumereList.Last.Value);
                    _deraumereList.RemoveLast();
                    Debug.Log("Deraumere Deleted");
                }
            }
            if (_siburList.Count < numberSibur)
            {
                diff = numberSibur - _siburList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.050f;
                    _foodList.AddLast(Instantiate(_sibur, _spawnPos, _rotation));
                }
            } else if (_siburList.Count > numberSibur)
            {
                diff = _siburList.Count - numberSibur;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_siburList.Last.Value);
                    _siburList.RemoveLast();
                    Debug.Log("Sibur Deleted");
                }
            }
            if (_mendianeList.Count < numberMendiane)
            {
                diff = numberMendiane - _mendianeList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.050f;
                    _foodList.AddLast(Instantiate(_mendiane, _spawnPos, _rotation));
                }
            }
            else if (_mendianeList.Count > numberMendiane)
            {
                diff = _mendianeList.Count - numberMendiane;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_mendianeList.Last.Value);
                    _mendianeList.RemoveLast();
                    Debug.Log("Mendiane Deleted");
                }
            }
            if (_phirasList.Count < numberPhiras)
            {
                diff = numberPhiras - _phirasList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.050f;
                    _foodList.AddLast(Instantiate(_phiras, _spawnPos, _rotation));
                }
            }
            else if (_phirasList.Count > numberPhiras)
            {
                diff = _phirasList.Count - numberPhiras;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_phirasList.Last.Value);
                    _phirasList.RemoveLast();
                    Debug.Log("Phiras Deleted");
                }
            }
            if (_thystameList.Count < numberThystame)
            {
                diff = numberThystame - _thystameList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.050f;
                    _foodList.AddLast(Instantiate(_thystame, _spawnPos, _rotation));
                }
            }
            else if (_thystameList.Count > numberThystame)
            {
                diff = _thystameList.Count - numberThystame;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_thystameList.Last.Value);
                    _thystameList.RemoveLast();
                    Debug.Log("Thystame Deleted");
                }
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

        public GameObject _food;
        public GameObject _linemate;
        public GameObject _deraumere;
        public GameObject _sibur;
        public GameObject _mendiane;
        public GameObject _phiras;
        public GameObject _thystame;
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
        else if (tmp == 200)
            receiveMessage = "ppo 0 14 0 4\n";
        else if (tmp == 400)
            receiveMessage = "ppo 0 14 14 3\n";
        else if (tmp == 600)
            receiveMessage = "ppo 0 0 14 2\n";
        else if (tmp == 800)
            receiveMessage = "ppo 0 0 0 1\n";
        else if (tmp == 510)
            receiveMessage = "bct 0 0 1 1 1 1 1 1 1\n";
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
            } else if (arguments[0] == "bct")
            {
                UpdateContentOfTile();
            }

        }
    }

    public void UpdateContentOfTile()
    {
        //-Server Reply: "bct X Y q0 q1 q2 q3 q4 q5 q6\n"
        if (arguments.Length >= 10)
        {
            foreach (Tile tile in map)
            {
                if (tile.GoodTileSelected(int.Parse(arguments[1]), int.Parse(arguments[2])))
                {
                    tile.UpdateTile(int.Parse(arguments[3]), int.Parse(arguments[4]), int.Parse(arguments[5]), int.Parse(arguments[6]),
                        int.Parse(arguments[7]), int.Parse(arguments[8]), int.Parse(arguments[9]));
                }    
            }
        } else
        {
            Debug.Log("bct: Reply missing argument.");
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
            characters.Add(int.Parse(arguments[1]), new Character(Instantiate(character), int.Parse(arguments[1]), int.Parse(arguments[2]), int.Parse(arguments[3]), int.Parse(arguments[4]), int.Parse(arguments[5]), arguments[6], mapSizeX, mapSizeY));
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
