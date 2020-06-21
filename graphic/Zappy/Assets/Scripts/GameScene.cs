using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.Threading.Tasks;
using TMPro;

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

    public GameObject elevation2;
    public GameObject elevation3;
    public GameObject elevation4;
    public GameObject elevation5;
    public GameObject elevation6;
    public GameObject elevation7;
    public GameObject elevation8;

    public GameObject egg;

    public GameObject rocket;
    public GameObject fire;

    public GameObject shockWave;

    public GameObject endScreen;
    public TextMeshProUGUI winTeamName;

    public GameObject hudTile;
    public TextMeshProUGUI numberFoodHudTile;
    public TextMeshProUGUI numberLinemateHudTile;
    public TextMeshProUGUI numberDeraumereHudTile;
    public TextMeshProUGUI numberSiburHudTile;
    public TextMeshProUGUI numberMendianeHudTile;
    public TextMeshProUGUI numberPhirasHudTile;
    public TextMeshProUGUI numberThystameHudTile;
    private int tileSelectedX = 0;
    private int tileSelectedY = 0;
    private float timeUpHudTile;


    public GameObject hudCharacter;
    public TextMeshProUGUI numberFoodHudCharacter;
    public TextMeshProUGUI numberLinemateHudCharacter;
    public TextMeshProUGUI numberDeraumereHudCharacter;
    public TextMeshProUGUI numberSiburHudCharacter;
    public TextMeshProUGUI numberMendianeHudCharacter;
    public TextMeshProUGUI numberPhirasHudCharacter;
    public TextMeshProUGUI numberThystameHudCharacter;
    public TextMeshProUGUI levelHudCharacter;
    public TextMeshProUGUI teamNameHudCharacter;
    private int characterSelected;
    private float timeUpHudCharacter;

    float timeUnit;

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
        public Character(GameObject gameObject, GameObject shockWave, int number, int posX, int posY, int orientation, int level, string teamName, int mapX, int mapY, float timeUnit, LinkedList<Tile> map,
            int tileSelectedX, int tileSelectedY, TextMeshProUGUI numberFoodHudTite, TextMeshProUGUI numberLinemateHudTite, TextMeshProUGUI numberDeraumereHudTite, TextMeshProUGUI numberSiburHudTite,
            TextMeshProUGUI numberMendianeHudTite, TextMeshProUGUI numberPhirasHudTite, TextMeshProUGUI numberThystameHudTite, int characterSelected, TextMeshProUGUI numberFoodHudCharacter, TextMeshProUGUI numberLinemateHudCharacter,
            TextMeshProUGUI numberDeraumereHudCharacter, TextMeshProUGUI numberSiburHudCharacter, TextMeshProUGUI numberMendianeHudCharacter, TextMeshProUGUI numberPhirasHudCharacter, TextMeshProUGUI numberThystameHudCharacter,
            TextMeshProUGUI levelHudCharacter, TextMeshProUGUI teamNameHudCharacter, GameObject elevation2, GameObject elevation3, GameObject elevation4, GameObject elevation5,GameObject elevation6,
            GameObject elevation7, GameObject elevation8)
        {
            _gameObject = gameObject;
            _shockWave = shockWave;
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
            _timeUnit = timeUnit;
            _numberFood = 0;
            _numberLinemate = 0;
            _numberDeraumere = 0;
            _numberSibur = 0;
            _numberMendiane = 0;
            _numberPhiras = 0;
            _numberThystame = 0;
            _map = map;
            _numberFoodHudTile = numberFoodHudTite;
            _numberLinemateHudTile = numberLinemateHudTite;
            _numberDeraumereHudTile = numberDeraumereHudTite;
            _numberSiburHudTile = numberSiburHudTite;
            _numberMendianeHudTile = numberMendianeHudTite;
            _numberPhirasHudTile = numberPhirasHudTite;
            _numberThystameHudTile = numberThystameHudTite;
            _tileSelectedX = tileSelectedX;
            _tileSelectedY = tileSelectedY;
            _numberFoodHudCharacter = numberFoodHudCharacter;
            _numberLinemateHudCharacter = numberLinemateHudCharacter;
            _numberDeraumereHudCharacter = numberDeraumereHudCharacter;
            _numberSiburHudCharacter = numberSiburHudCharacter;
            _numberMendianeHudCharacter = numberMendianeHudCharacter;
            _numberPhirasHudCharacter = numberPhirasHudCharacter;
            _numberThystameHudCharacter = numberThystameHudCharacter;
            _teamNameHudCharacter = teamNameHudCharacter;
            _levelHudCharacter = levelHudCharacter;
            _characterSelected = characterSelected;
            _elevation2 = elevation2;
            _elevation3 = elevation3;
            _elevation4 = elevation4;
            _elevation5 = elevation5;
            _elevation6 = elevation6;
            _elevation7 = elevation7;
            _elevation8 = elevation8;
            _elevations = new LinkedList<Elevation>();
            _waitingActions = new LinkedList<string>();
            _actionInProgress = false;
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
            _gameObject.transform.position = new Vector3(UnityEngine.Random.Range(posX + 0.2f, posX + 0.8f), 0, UnityEngine.Random.Range(posY + 0.2f, posY + 0.8f));
        }

        public void SetPointToMove(int posX, int posY)
        {
            _posToMoveX = posX;
            _posToMoveY = posY;
        }

        public bool NeedToTP()
        {
            if (_posToMoveX != _posX && _posToMoveY != _posY)
                return true;
            return false;
        }

        public bool NeedToMove()
        {
            if (_posToMoveX == _posX && _posToMoveY == _posY)
            {
                _animator.SetInteger("run", 0);
                _actionInProgress = false;
                return false;
            }
            _animator.SetInteger("run", 1);
            _actionInProgress = true;
            return true;
        }

        public void Move() /// Boucle
        {
            bool posXReached = false;
            bool posYReached = false;

            _actionInProgress = true;
            if (_posToMoveX > _posX && _posToMoveX >= _mapX - 1 && _posX <= 0) /// Gauche de la map TP droite
            {
                _gameObject.transform.Translate(-0.5f * Time.deltaTime * _timeUnit, 0, 0, Space.World);
                if (_gameObject.transform.position.x < 0f)
                    _gameObject.transform.position = new Vector3(_mapX, 0, _posY);
            }
            else if (_posToMoveX < _posX && _posToMoveX == 0 && _posX >= _mapX - 1) /// Droite de la map TP gauche
            {
                _gameObject.transform.Translate(0.5f * Time.deltaTime * _timeUnit, 0, 0, Space.World);
                if (_gameObject.transform.position.x > _mapX)
                    _gameObject.transform.position = new Vector3(0, 0, _posY);
            }
            else if (_posToMoveY > _posY && _posToMoveY == _mapY - 1 && _posY <= 0) /// Bas de la map TP haut
            {
                _gameObject.transform.Translate(0, 0, -0.5f * Time.deltaTime * _timeUnit, Space.World);
                if (_gameObject.transform.position.z < 0f)
                    _gameObject.transform.position = new Vector3(_posX, 0, _mapY);
            }
            else if (_posToMoveY < _posY && _posToMoveY == 0 && _posY >= _mapY - 1) /// Haut de la map TP bas
            {
                _gameObject.transform.Translate(0, 0, 0.5f * Time.deltaTime * _timeUnit, Space.World);
                if (_gameObject.transform.position.z > _mapY)
                    _gameObject.transform.position = new Vector3(_posX, 0, 0);
            }
            else
            {
                if (_posToMoveX > _posX)
                    _gameObject.transform.Translate(0.5f * Time.deltaTime * _timeUnit, 0, 0, Space.World);
                if (_posToMoveY > _posY)
                    _gameObject.transform.Translate(0, 0, 0.5f * Time.deltaTime * _timeUnit, Space.World);
                if (_posToMoveX < _posX)
                    _gameObject.transform.Translate(-0.5f * Time.deltaTime * _timeUnit, 0, 0, Space.World);
                if (_posToMoveY < _posY)
                    _gameObject.transform.Translate(0, 0, -0.5f * Time.deltaTime * _timeUnit, Space.World);
            }

            if (_posX > _posToMoveX && _gameObject.transform.position.x - 0.75 <= _posToMoveX)
            {
                _posX = _posToMoveX;
                posXReached = true;
                if (_timeUnit >= 20)
                {
                    SetPosition(_posToMoveX, _posToMoveY);
                }
            }
            else if (_posX < _posToMoveX && _gameObject.transform.position.x - 0.25f >= _posToMoveX)
            {
                _posX = _posToMoveX;
                posXReached = true;
                if (_timeUnit >= 20)
                {
                    SetPosition(_posToMoveX, _posToMoveY);
                }
            }
            if (_posY > _posToMoveY && _gameObject.transform.position.z - 0.75 <= _posToMoveY)
            {
                _posY = _posToMoveY;
                posYReached = true;
                if (_timeUnit >= 20)
                {
                    SetPosition(_posToMoveX, _posToMoveY);
                }
            }
            if (_posY < _posToMoveY && _gameObject.transform.position.z - 0.25f >= _posToMoveY)
            {
                _posY = _posToMoveY;
                posYReached = true;
                if (_timeUnit >= 20)
                {
                    SetPosition(_posToMoveX, _posToMoveY);
                }
            }
            if (posXReached == true && posYReached == true)
                _actionInProgress = false;
        }

        public void AddNewAction(string action)
        {
            _waitingActions.AddLast(action);
        }

        public void Update() /// Boucle
        {
            string[] args;

            //Debug.Log(_waitingActions.Count);
            if (_waitingActions.Count > 0 && _actionInProgress == false)
            {
                //Debug.Log("Action in progress: " + _waitingActions.First.Value);
                args = _waitingActions.First.Value.Split(' ');
                _waitingActions.RemoveFirst();

                if (args[0] == "ppo")
                {
                    SetPointToMove(int.Parse(args[2]), int.Parse(args[3]));
                    SetOrientation(int.Parse(args[4]));
                } else if (args[0] == "bct")
                {
                    UpdateTile(args);
                } else if (args[0] == "pin")
                {
                    UpdatePlayerInventory(args);
                } else if (args[0] == "pic")
                {
                    StartIncantation(args);
                } else if (args[0] == "pie")
                {
                    EndOfIncantation(args);
                } else if (args[0] == "pbc")
                {
                    StartBroadcast();
                } else if (args[0] == "plv")
                {
                    SetPlayerLevel(args);
                }
            }
            if (NeedToTP())
                SetPosition(_posToMoveX, _posToMoveY);
            else if (NeedToMove())
            {
                Move();
            }
        }

        public void SetPlayerLevel(string[] args)
        {
            SetLevel(int.Parse(args[2]));
            if (_gameObject.GetInstanceID() == _characterSelected)
            {
                _levelHudCharacter.text = "Level: " + GetLevel().ToString();
            }
        }

        public void EndOfIncantation(string[] args)
        {
            foreach (Elevation elev in _elevations)
            {
                if (elev.GoodElevationSelected(int.Parse(args[2]), int.Parse(args[3])))
                {
                    elev.DestroyElevation();
                    _elevations.Remove(elev);
                    break;
                }
            }
        }

        private void StartIncantation(string[] args)
        {
            if (args[3] == "1")
                _elevations.AddLast(new Elevation(_elevation2, int.Parse(args[1]), int.Parse(args[2])));
            else if (args[3] == "2")
                _elevations.AddLast(new Elevation(_elevation3, int.Parse(args[1]), int.Parse(args[2])));
            else if (args[3] == "3")
                _elevations.AddLast(new Elevation(_elevation4, int.Parse(args[1]), int.Parse(args[2])));
            else if (args[3] == "4")
                _elevations.AddLast(new Elevation(_elevation5, int.Parse(args[1]), int.Parse(args[2])));
            else if (args[3] == "5")
                _elevations.AddLast(new Elevation(_elevation6, int.Parse(args[1]), int.Parse(args[2])));
            else if (args[3] == "6")
                _elevations.AddLast(new Elevation(_elevation7, int.Parse(args[1]), int.Parse(args[2])));
            else if (args[3] == "7")
                _elevations.AddLast(new Elevation(_elevation8, int.Parse(args[1]), int.Parse(args[2])));
        }

        private void UpdatePlayerInventory(string[] args)
        {
            int[] inventory = {int.Parse(args[2]), int.Parse(args[3]), int.Parse(args[4]), int.Parse(args[5]),
                int.Parse(args[6]), int.Parse(args[7]), int.Parse(args[8])};
            SetInventory(inventory);

            if (_gameObject.GetInstanceID() == _characterSelected)
            {
                _teamNameHudCharacter.text = GetTeamName();
                _numberFoodHudCharacter.text = inventory[0].ToString();
                _numberLinemateHudCharacter.text = inventory[1].ToString();
                _numberDeraumereHudCharacter.text = inventory[2].ToString();
                _numberSiburHudCharacter.text = inventory[3].ToString();
                _numberMendianeHudCharacter.text = inventory[4].ToString();
                _numberPhirasHudCharacter.text = inventory[5].ToString();
                _numberThystameHudCharacter.text = inventory[6].ToString();
            }
        }

        private void UpdateTile(string[] args)
        {
            int[] infos;
            foreach (Tile tile in _map)
            {
                if (tile.GoodTileSelected(int.Parse(args[2]), int.Parse(args[3])))
                {
                    tile.UpdateTile(int.Parse(args[4]), int.Parse(args[5]), int.Parse(args[6]), int.Parse(args[7]),
                        int.Parse(args[8]), int.Parse(args[9]), int.Parse(args[10]));
                    if (_tileSelectedX == int.Parse(args[2]) && _tileSelectedY == int.Parse(args[3]))
                    {
                        infos = tile.GetInfoTile();
                        _numberFoodHudTile.text = infos[0].ToString();
                        _numberLinemateHudTile.text = infos[1].ToString();
                        _numberDeraumereHudTile.text = infos[2].ToString();
                        _numberSiburHudTile.text = infos[3].ToString();
                        _numberMendianeHudTile.text = infos[4].ToString();
                        _numberPhirasHudTile.text = infos[5].ToString();
                        _numberThystameHudTile.text = infos[6].ToString();
                    }
                }
            }
        }

        public void UpdateCharacterSelected(int characterSelected)
        {
            _characterSelected = characterSelected;
        }

        public void UpdateTileSelected(int posX, int posY)
        {
            _tileSelectedX = posX;
            _tileSelectedX = posY;
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

        public void StartBroadcast()
        {
            _shockWave.SetActive(false);
            _shockWave = Instantiate(_shockWave, new Vector3(_posX + 0.5f, 0f, _posY + 0.5f), new Quaternion(0f, 0f, 0f, 0f));
            _shockWave.SetActive(true);
            _timeBroadcast = Time.time;
        }

        public void CheckEndBroadcast()
        {
            if (Time.time - _timeBroadcast >= 0.80)
            {
                _shockWave.SetActive(false); ;
            }
        }

        public void SetLevel(int level)
        {
            _level = level;
        }

        public void SetInventory(int[] inventory)
        {
            _numberFood = inventory[0];
            _numberLinemate = inventory[1];
            _numberDeraumere = inventory[2];
            _numberSibur = inventory[3];
            _numberMendiane = inventory[4];
            _numberPhiras = inventory[5];
            _numberThystame = inventory[6];
        }

        public float GetXPos()
        {
            return _posX;
        }

        public float GetYPos()
        {
            return _posY;
        }

        public int GetGameObjectInstanceID()
        {
            return _gameObject.GetInstanceID();
        }

        public int GetNumber()
        {
            return _number;
        }

        public int GetLevel()
        {
            return _level;
        }

        public string GetTeamName()
        {
            return _teamName;
        }

        public int[] GetInventory()
        {
            int[] result = { _numberFood, _numberLinemate, _numberDeraumere, _numberSibur, _numberMendiane, _numberPhiras, _numberThystame};
            return result;
        }

        public void DestroyPlayer()
        {
            Destroy(_gameObject);
        }

        private GameObject _gameObject;
        private Animator _animator;
        private GameObject _shockWave;
        private float _timeBroadcast;
        private int _posX;
        private int _posY;
        private int _posToMoveX;
        private int _posToMoveY;
        private int _orientation;
        private int _mapX;
        private int _mapY;
        private float _timeUnit;

        private int _number;
        private int _level;
        private string _teamName;
        private int _numberFood;
        private int _numberLinemate;
        private int _numberDeraumere;
        private int _numberSibur;
        private int _numberMendiane;
        private int _numberPhiras;
        private int _numberThystame;


        private TextMeshProUGUI _numberFoodHudTile;
        private TextMeshProUGUI _numberLinemateHudTile;
        private TextMeshProUGUI _numberDeraumereHudTile;
        private TextMeshProUGUI _numberSiburHudTile;
        private TextMeshProUGUI _numberMendianeHudTile;
        private TextMeshProUGUI _numberPhirasHudTile;
        private TextMeshProUGUI _numberThystameHudTile;
        private int _tileSelectedX;
        private int _tileSelectedY;

        private TextMeshProUGUI _numberFoodHudCharacter;
        private TextMeshProUGUI _numberLinemateHudCharacter;
        private TextMeshProUGUI _numberDeraumereHudCharacter;
        private TextMeshProUGUI _numberSiburHudCharacter;
        private TextMeshProUGUI _numberMendianeHudCharacter;
        private TextMeshProUGUI _numberPhirasHudCharacter;
        private TextMeshProUGUI _numberThystameHudCharacter;
        private TextMeshProUGUI _levelHudCharacter;
        private TextMeshProUGUI _teamNameHudCharacter;

        public GameObject _elevation2;
        public GameObject _elevation3;
        public GameObject _elevation4;
        public GameObject _elevation5;
        public GameObject _elevation6;
        public GameObject _elevation7;
        public GameObject _elevation8;

        private LinkedList<Elevation> _elevations;

        private int _characterSelected;

        private LinkedList<Tile> _map;
        private LinkedList<string> _waitingActions;
        bool _actionInProgress;
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

            _foodNumber = numberFood;
            _linemateNumber = numberLinemate;
            _deraumereNumber = numberDeraumere;
            _siburNumber = numberSibur;
            _mendianeNumber = numberMendiane;
            _phirasNumber = numberPhiras;
            _thystameNumber = numberThystame;

            //print("x: " + posX + " y: " + posY + " | Food: " + numberFood + " | Linemate: " + numberLinemate + " | Deraumere: " + numberDeraumere + " | Sibur: " 
            //    + numberSibur + " | Mendiane: " + numberMendiane + " | phiras: " + numberPhiras + " | thystame: " + numberThystame);
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
            //print("x: " + posX + " y: " + posY + " | Food: " + _foodList.Count + " | Linemate: " + _linemateList.Count + " | Deraumere: " + _deraumereList.Count + " | Sibur: "
            //    + _siburList.Count + " | Mendiane: " + _mendianeList.Count + " | phiras: " + _phirasList.Count + " | thystame: " + _thystameList.Count);
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

            _foodNumber = numberFood;
            _linemateNumber = numberLinemate;
            _deraumereNumber = numberDeraumere;
            _siburNumber = numberSibur;
            _mendianeNumber = numberMendiane;
            _phirasNumber = numberPhiras;
            _thystameNumber = numberThystame;

            //print("Food: " + numberFood + " | Linemate: " + numberLinemate + " | Deraumere: " + numberDeraumere + " | Sibur: "
            //     + numberSibur + " | Mendiane: " + numberMendiane + " | phiras: " + numberPhiras + " | thystame: " + numberThystame);
            //print("Food: " + _foodList.Count + " | Linemate: " + _linemateList.Count + " | Deraumere: " + _deraumereList.Count + " | Sibur: "
            //    + _siburList.Count + " | Mendiane: " + _mendianeList.Count + " | phiras: " + _phirasList.Count + " | thystame: " + _thystameList.Count);

            if (_foodList.Count < numberFood)
            {
                diff = numberFood - _foodList.Count;
                for (int i = 0; i < diff; i++)
                {
                    _spawnPos.x = UnityEngine.Random.Range(_posX, _posX + 1f);
                    _spawnPos.z = UnityEngine.Random.Range(_posY, _posY + 1f);
                    _spawnPos.y = 0.1f;
                    _foodList.AddLast(Instantiate(_food, _spawnPos, _rotation));
                    Debug.Log("Food Created");
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
                    _linemateList.AddLast(Instantiate(_linemate, _spawnPos, _rotation));
                    Debug.Log("Linemate Created");
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
                    _deraumereList.AddLast(Instantiate(_deraumere, _spawnPos, _rotation));
                    print("Deraumere Created");
                }
            } else if (_deraumereList.Count > numberDeraumere)
            {
                diff = _deraumereList.Count - numberDeraumere;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_deraumereList.Last.Value);
                    _deraumereList.RemoveLast();
                    print("Deraumere Deleted");
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
                    _siburList.AddLast(Instantiate(_sibur, _spawnPos, _rotation));
                    print("Sibur Created");
                }
            } else if (_siburList.Count > numberSibur)
            {
                diff = _siburList.Count - numberSibur;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_siburList.Last.Value);
                    _siburList.RemoveLast();
                    print("Sibur Deleted");
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
                    _mendianeList.AddLast(Instantiate(_mendiane, _spawnPos, _rotation));
                    print("Sibur Created");
                }
            }
            else if (_mendianeList.Count > numberMendiane)
            {
                diff = _mendianeList.Count - numberMendiane;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_mendianeList.Last.Value);
                    _mendianeList.RemoveLast();
                    print("Sibur Deleted");
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
                    _phirasList.AddLast(Instantiate(_phiras, _spawnPos, _rotation));
                    print("Phiras Created");
                }
            }
            else if (_phirasList.Count > numberPhiras)
            {
                diff = _phirasList.Count - numberPhiras;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_phirasList.Last.Value);
                    _phirasList.RemoveLast();
                    print("Phiras Deleted");
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
                    _thystameList.AddLast(Instantiate(_thystame, _spawnPos, _rotation));
                    print("Thystame Created");
                }
            }
            else if (_thystameList.Count > numberThystame)
            {
                diff = _thystameList.Count - numberThystame;

                for (int i = 0; i < diff; i++)
                {
                    Destroy(_thystameList.Last.Value);
                    _thystameList.RemoveLast();
                    print("Thystame Deleted");
                }
            }
        }

        public int[] GetInfoTile()
        {
            int[] result = { _foodNumber, _linemateNumber, _deraumereNumber, _siburNumber, _mendianeNumber, _phirasNumber, _thystameNumber};
            return result;
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

        private int _foodNumber;
        private int _linemateNumber;
        private int _deraumereNumber;
        private int _siburNumber;
        private int _mendianeNumber;
        private int _phirasNumber;
        private int _thystameNumber;

        public GameObject _food;
        public GameObject _linemate;
        public GameObject _deraumere;
        public GameObject _sibur;
        public GameObject _mendiane;
        public GameObject _phiras;
        public GameObject _thystame;
    }
    private LinkedList<Tile> map;

    private class Elevation
    {
        public Elevation(GameObject elev, int posX, int posY)
        {
            _elev = elev;
            _posX = posX;
            _posY = posY;
            _rotation = new Quaternion(0f, 0f, 0f, 0f);
            _spawnPos.x = posX + 0.5f;
            _spawnPos.z = posY + 0.5f;
            _spawnPos.y = 0.1f;
            _elev = Instantiate(elev, _spawnPos, _rotation);
        }

        public bool GoodElevationSelected(int posX, int posY)
        {
            if (_posX == posX && _posY == posY)
                return true;
            return false;
        }

        public void DestroyElevation()
        {
            Destroy(_elev);
        }

        private int _posX;
        private int _posY;

        private Vector3 _spawnPos;
        private Quaternion _rotation;
        private GameObject _elev;
    }
    private LinkedList<Elevation> elevations;

    private class Egg
    {
        public Egg(GameObject egg, int posX, int posY)
        {
            _posX = posX;
            _posY = posY;
           _egg = Instantiate(egg, new Vector3(UnityEngine.Random.Range(posX + 0.1f, posX + 0.9f), 0.160f, UnityEngine.Random.Range(posY + 0.1f, posY + 0.9f)), new Quaternion(0f, 0f, 0f, 0f));
        }

        public void DeleteEgg()
        {
            Destroy(_egg);
        }

        GameObject _egg;
        int _posX;
        int _posY;
    }
    private Dictionary<int, Egg> eggs;

    private bool end;

    private LinkedList<string> waitingActions;
    private bool actionInProgress;

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
        elevations = new LinkedList<Elevation>();
        eggs = new Dictionary<int, Egg>();
        waitingActions = new LinkedList<string>();
        actionInProgress = false;
        end = false;

        GetTimeUnit();
        SetUpAssetsSize();
        SetUpSizeMap();
        SetUpMap();
        GetTeamsName();
    }

    // Update is called once per frame
    void Update()
    {
        string[] args;

        ReceiveMessageFromServer();
        if (waitingActions.Count > 0 && actionInProgress == false)
        {

        }
        foreach (KeyValuePair<int, Character> kvp in characters)
        {
            characters[kvp.Key].Update();
            characters[kvp.Key].CheckEndBroadcast();
        }
        if (Time.fixedTime - timeUpHudCharacter >= 20)
        {
            hudCharacter.SetActive(false);
        }
        if (Time.fixedTime - timeUpHudTile >= 20)
        {
            hudTile.SetActive(false);
        }

        if (end == true)
        {
            rocket.transform.Translate(0f, 5f * Time.deltaTime, 0f, Space.World);
            fire.transform.Translate(0f, 5f * Time.deltaTime, 0f, Space.World);
        }

        if (Input.GetKeyUp(KeyCode.Escape))
        {
            if (PauseMenu.activeSelf)
                PauseMenu.SetActive(false);
            else
                PauseMenu.SetActive(true);
        }
    }

    public void ReceiveMessageFromServer()
    {
        receiveMessage = client.ReceiveMesageFromServer();
        if (receiveMessage != null)
        {
            Array.Clear(arguments, 0, arguments.Length);
            arguments = receiveMessage.Split(' ');
            if (arguments[0] == "pnw")
                InstantiateNewPlayer();
            else if (arguments[0] == "ppo")
                SetPointToMovePlayer(receiveMessage);
            else if (arguments[0] == "bct")
                UpdateContentOfTile(receiveMessage);
            else if (arguments[0] == "pic")
                StartIncantation(receiveMessage);
            else if (arguments[0] == "pie")
                EndIncantation(receiveMessage);
            else if (arguments[0] == "pdi")
                DieOfPlayer(receiveMessage);
            else if (arguments[0] == "seg")
                EndOfTheGame();
            else if (arguments[0] == "enw")
                CreateEgg();
            else if (arguments[0] == "eht")
                DeleteEgg();
            else if (arguments[0] == "pbc")
                StartBroadcast(receiveMessage);
            else if (arguments[0] == "plv")
                SetLevelPlayer(receiveMessage);
            else if (arguments[0] == "pin")
                SetInventoryPlayer(receiveMessage);
        }
    }

    public void SetInventoryPlayer(string receiveMessage)
    {
        int[] inventory;
        int rank = 0;

        if (arguments.Length >= 9)
        { 
            rank = int.Parse(arguments[1]);
            characters[rank].AddNewAction(receiveMessage);
        } else
        {
            Debug.Log("pin: Reply missing argument.");
        }
    }

    public void SetLevelPlayer(string receiveMessage)
    {
        int rank = 0;

        if (arguments.Length >= 3)
        {
            //characters[rank].AddNewAction(receiveMessage);
            rank = int.Parse(arguments[1]);
            characters[rank].SetLevel(int.Parse(arguments[2]));
            if (characters[rank].GetGameObjectInstanceID() == characterSelected)
            {
                levelHudCharacter.text = "Level: " + characters[rank].GetLevel().ToString();
            }
        } else
        {
            Debug.Log("plv: Reply missing argument.");
        }
    }

    public void GetTimeUnit()
    {
        client.SendMessageToServer("sgt\n");
        receiveMessage = client.WaitMessageFromServer();

        if (receiveMessage != null)
        {
            arguments = receiveMessage.Split(' ');
            if (arguments[0] == "sgt" && arguments.Length >= 2)
            {
                timeUnit = float.Parse(arguments[1]);
            } 
        }
    }
    
    public void StartBroadcast(string receiveMessage)
    {
        if (arguments.Length >= 2)
        {
            characters[int.Parse(arguments[1])].AddNewAction(receiveMessage);
        }
        else
        {
            Debug.Log("pbc: Reply missing argument.");
        }
    }

    public void DeleteEgg()
    {
        if (arguments.Length >= 2)
        {
            eggs[int.Parse(arguments[1])].DeleteEgg();
            eggs.Remove(int.Parse(arguments[1]));
        }
        else
        {
            Debug.Log("seg: Reply missing argument.");
        }
    }

    public void CreateEgg()
    {
        if (arguments.Length >= 4)
        {
            eggs.Add(int.Parse(arguments[1]), new Egg(egg, int.Parse(arguments[2]), int.Parse(arguments[3])));
        } else
        {
            Debug.Log("seg: Reply missing argument.");
        }
    }

    public void EndOfTheGame()
    {
        if (arguments.Length >= 2)
        {
            spawnPos = new Vector3(mapSizeX / 2, 2.35f, mapSizeY / 2);
            rotation = new Quaternion(0f, 0f, 0f, 0f);
            rocket = Instantiate(rocket, spawnPos, rotation);
            spawnPos = new Vector3(mapSizeX / 2, -0.25f, mapSizeY / 2);
            rotation = new Quaternion(0f, 0f, 180f, 0f);
            fire = Instantiate(fire, spawnPos, rotation);
            endScreen.SetActive(true);
            winTeamName.text = arguments[1] + "WIN !";
            end = true;
        } else
        {
            Debug.Log("seg: Reply missing argument.");
        }
    }

    public void DieOfPlayer(string receiveMessage)
    {
        if (arguments.Length >= 2)
        {
            characters[int.Parse(arguments[1])].AddNewAction(receiveMessage);
            //characters[int.Parse(arguments[1])].DestroyPlayer();
            //characters.Remove(int.Parse(arguments[1]));
        }
        else
        {
            Debug.Log("pdi: Reply missing argument.");
        }
    }

    public void EndIncantation(string receiveMessage)
    {
        if (arguments.Length >= 5) {
            characters[int.Parse(arguments[1])].AddNewAction(receiveMessage);
            //foreach (Elevation elev in elevations)
            //{
            //    if (elev.GoodElevationSelected(int.Parse(arguments[1]), int.Parse(arguments[2])))
            //    {
            //        elev.DestroyElevation();
            //        elevations.Remove(elev);
            //        break;
            //    }
            //}
        }
        else
        {
            Debug.Log("pie: Reply missing argument.");
        }
    }

    public void StartIncantation(string receiveMessage)
    {
        if (arguments.Length >= 5) {
            characters[int.Parse(arguments[4])].AddNewAction(receiveMessage);
            //if (arguments[3] == "1")
            //    elevations.AddLast(new Elevation(elevation2, int.Parse(arguments[1]), int.Parse(arguments[2])));
            //else if (arguments[3] == "2")
            //    elevations.AddLast(new Elevation(elevation3, int.Parse(arguments[1]), int.Parse(arguments[2])));
            //else if (arguments[3] == "3")
            //    elevations.AddLast(new Elevation(elevation4, int.Parse(arguments[1]), int.Parse(arguments[2])));
            //else if (arguments[3] == "4")
            //    elevations.AddLast(new Elevation(elevation5, int.Parse(arguments[1]), int.Parse(arguments[2])));
            //else if (arguments[3] == "5")
            //    elevations.AddLast(new Elevation(elevation6, int.Parse(arguments[1]), int.Parse(arguments[2])));
            //else if (arguments[3] == "6")
            //    elevations.AddLast(new Elevation(elevation7, int.Parse(arguments[1]), int.Parse(arguments[2])));
            //else if (arguments[3] == "7")
            //    elevations.AddLast(new Elevation(elevation8, int.Parse(arguments[1]), int.Parse(arguments[2])));
        }
        else
        {
            Debug.Log("pic: Reply missing argument.");
        }
    }

    public void UpdateContentOfTile(string receiveMessage)
    {
        int[] infos;

        if (arguments.Length >= 10)
        {
            if (int.Parse(arguments[1]) != -1)
            {
                characters[int.Parse(arguments[1])].AddNewAction(receiveMessage);
            }
            else
            {
                foreach (Tile tile in map)
                {
                    if (tile.GoodTileSelected(int.Parse(arguments[1]), int.Parse(arguments[2])))
                    {
                        tile.UpdateTile(int.Parse(arguments[3]), int.Parse(arguments[4]), int.Parse(arguments[5]), int.Parse(arguments[6]),
                            int.Parse(arguments[7]), int.Parse(arguments[8]), int.Parse(arguments[9]));
                        if (tileSelectedX == int.Parse(arguments[1]) && tileSelectedY == int.Parse(arguments[2]))
                        {
                            infos = tile.GetInfoTile();
                            numberFoodHudTile.text = infos[0].ToString();
                            numberLinemateHudTile.text = infos[1].ToString();
                            numberDeraumereHudTile.text = infos[2].ToString();
                            numberSiburHudTile.text = infos[3].ToString();
                            numberMendianeHudTile.text = infos[4].ToString();
                            numberPhirasHudTile.text = infos[5].ToString();
                            numberThystameHudTile.text = infos[6].ToString();
                        }
                    }
                }
            }
        } else
        {
            Debug.Log("bct: Reply missing argument.");
        }

    }

    public void SetPointToMovePlayer(string receiveMessage)
    {
        if (arguments.Length >= 5)
        {
            characters[int.Parse(arguments[1])].AddNewAction(receiveMessage);
        }
        else
        {
            Debug.Log("ppo: Reply missing argument.");
        }
    }

    public void InstantiateNewPlayer()
    {
        if (arguments.Length >= 7)
        {
            characters.Add(int.Parse(arguments[1]), new Character(Instantiate(character), shockWave, int.Parse(arguments[1]), int.Parse(arguments[2]), int.Parse(arguments[3]), int.Parse(arguments[4]), int.Parse(arguments[5]),
                arguments[6], mapSizeX, mapSizeY, timeUnit, map, tileSelectedX, tileSelectedY, numberFoodHudTile, numberLinemateHudTile, numberDeraumereHudTile, numberSiburHudTile, numberMendianeHudTile, numberPhirasHudTile,
                numberThystameHudTile, characterSelected, numberFoodHudCharacter, numberLinemateHudCharacter, numberDeraumereHudCharacter, numberSiburHudCharacter, numberMendianeHudCharacter, numberPhirasHudCharacter,
                numberThystameHudCharacter, levelHudCharacter, teamNameHudCharacter, elevation2, elevation3, elevation4, elevation5, elevation6, elevation7, elevation8));
        } else
        {
            Debug.Log("pnw: Reply missing argument.");
        }
    }

    public void GetTeamsName()
    {
        teams = new LinkedList<string>();
        client.SendMessageToServer("tna\n");
        receiveMessage = client.WaitMessageFromServer();

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
            Array.Clear(arguments, 0, arguments.Length);
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
        float maxDiffX = mapSizeX / 2;
        float diffX = 0f;
        float pourcX = 0f;

        float maxDiffY = mapSizeY / 2;
        float diffY = 0f;
        float pourcY = 0f;

        float maxSize = 0f;

        //if (mapSizeX <= mapSizeY)
        //{
        for (int y = 0; y < mapSizeY; y++)
        {
            for (int x = 0; x < mapSizeX; x++)
            {
                diffX = x - mapSizeX / 2;
                if (diffX < 0)
                    diffX = -diffX;
                pourcX = diffX * 100 / maxDiffX;
                pourcX = 100 - pourcX;

                diffY = y - mapSizeY / 2;
                if (diffY < 0)
                    diffY = -diffY;
                pourcY = diffY * 100 / maxDiffY;
                pourcY = 100 - pourcY;

                maxSize = UnityEngine.Random.Range(1f, pourcX / 11 + pourcY / 11);
                if (maxSize < 1f)
                    maxSize = 1f;
                client.SendMessageToServer("bct " + x + " " + y + "\n");
                plane.transform.localScale = new Vector3(1f, maxSize, 1f);
                mapPos.y = -plane.transform.localScale.y / 2;
                Instantiate(plane, mapPos, rotation);
                SetUpTile(x, y);
                mapPos.x += 1f;
            }
            mapPos.z += 1f;
            mapPos.x = startPointZ;
        }
        //}
        //else
        //{
        //    for (int x = 0; x < mapSizeX; x++)
        //    {
        //        for (int y = 0; y < mapSizeY; y++)
        //        {
        //            if (maxSize < 1f)
        //                maxSize = 1f;
        //            client.SendMessageToServer("bct " + x + " " + y + "\n");
        //            plane.transform.localScale = new Vector3(1f, maxSize, 1f);
        //            mapPos.y = -plane.transform.localScale.y / 2;
        //            Instantiate(plane, mapPos, rotation);
        //            SetUpTile(x, y);
        //            mapPos.z += 1f;
        //        }
        //        mapPos.x += 1f;
        //        mapPos.z = startPointZ;
        //    }
        //}
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
                if (arguments.Length >= 11)
                {
                    map.AddLast(new Tile(x, y, int.Parse(arguments[4]), int.Parse(arguments[5]), int.Parse(arguments[6]), int.Parse(arguments[7]), int.Parse(arguments[8]), int.Parse(arguments[9]),
                    int.Parse(arguments[10]), mapPos, food, linemate, deraumere, sibur, mendiane, phiras, thystame));
                }
                else
                {
                    Debug.Log("bct: Reply missing argument.");
                    Application.Quit();
                }
            }
        }
    }

    public void GetInfoTileSelected(int posX, int posY)
    {
        int[] infos;

        foreach (Tile tile in map)
        {
            if (tile.GoodTileSelected(posX, posY))
            {
                foreach (KeyValuePair<int, Character> kvp in characters)
                {
                    characters[kvp.Key].UpdateTileSelected(posX, posY);
                }

                timeUpHudTile = Time.fixedTime;
                infos = tile.GetInfoTile();
                hudTile.SetActive(true);
                numberFoodHudTile.text = infos[0].ToString();
                numberLinemateHudTile.text = infos[1].ToString();
                numberDeraumereHudTile.text = infos[2].ToString();
                numberSiburHudTile.text = infos[3].ToString();
                numberMendianeHudTile.text = infos[4].ToString();
                numberPhirasHudTile.text = infos[5].ToString();
                numberThystameHudTile.text = infos[6].ToString();
            }
        }
    }

    public void GetInfoCharacterSelected(int gameObjectInstanceID)
    {
        int[] infos;

        foreach (KeyValuePair<int, Character> kvp in characters)
        {
            if (characters[kvp.Key].GetGameObjectInstanceID() == gameObjectInstanceID)
            {
                characterSelected = gameObjectInstanceID;
                foreach (KeyValuePair<int, Character> chara in characters)
                {
                    characters[chara.Key].UpdateCharacterSelected(characterSelected);
                }
                timeUpHudCharacter = Time.fixedTime;
                hudCharacter.SetActive(true);
                levelHudCharacter.text = "Level: " + characters[kvp.Key].GetLevel().ToString();
                teamNameHudCharacter.text = characters[kvp.Key].GetTeamName();
                infos = characters[kvp.Key].GetInventory();
                numberFoodHudCharacter.text = infos[0].ToString();
                numberLinemateHudCharacter.text = infos[1].ToString();
                numberDeraumereHudCharacter.text = infos[2].ToString();
                numberSiburHudCharacter.text = infos[3].ToString();
                numberMendianeHudCharacter.text = infos[4].ToString();
                numberPhirasHudCharacter.text = infos[5].ToString();
                numberThystameHudCharacter.text = infos[6].ToString();
            }
        }
    }
}
