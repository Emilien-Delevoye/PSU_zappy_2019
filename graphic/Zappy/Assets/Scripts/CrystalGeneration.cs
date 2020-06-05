using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrystalGeneration : MonoBehaviour
{
    private Vector3 pos;
    private Quaternion rotation;
    public GameObject spawnee;

    // Start is called before the first frame update
    void Start()
    {
        pos.x = 0f;
        pos.y = 0.050f;
        pos.z = 0;
        rotation.x = 0;
        rotation.y = 0;
        rotation.z = 0;
        spawnee.transform.localScale = new Vector3(0.4f, 0.4f, 0.4f);
        for (int i = 0; i < 40; i++)
        {
            pos.x = Random.Range(-5f, 5f);
            pos.z = Random.Range(-5f, 5f);
            Instantiate(spawnee, pos, rotation);
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
