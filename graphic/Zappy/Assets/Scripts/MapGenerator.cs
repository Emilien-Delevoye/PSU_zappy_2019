using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapGenerator : MonoBehaviour
{
    public GameObject plane;

    private Vector3 pos;
    private Quaternion rotation;

    private int mapSizeX = 10;
    private int mapSizeZ = 10;

    private float startPointX = 0.5f;
    private float startPointZ = 0.5f;

    // Start is called before the first frame update
    void Start()
    {
        rotation.x = 0f;
        rotation.y = 0f;
        rotation.z = 0f;
        pos.x = startPointX;
        pos.z = startPointZ;

        if (mapSizeX < mapSizeZ)
        {
            for (int i = 0; i < mapSizeZ; i++)
            {
                for (int j = 0; j < mapSizeX; j++)
                {
                    Instantiate(plane, pos, rotation);
                    pos.x += 1f;
                }
                pos.z += 1f;
                pos.x = startPointZ;
            }
        } else
        {
            for (int i = 0; i < mapSizeX; i++)
            {
                for (int j = 0; j < mapSizeZ; j++)
                {
                    Instantiate(plane, pos, rotation);
                    pos.z += 1f;
                }
                pos.x += 1f;
                pos.z = startPointZ;
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
