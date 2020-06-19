using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetInfoTile : MonoBehaviour
{
    private GameScene gameScene;

    private void Awake()
    {
        gameScene = GameObject.FindObjectOfType<GameScene>();
    }

    private void OnMouseDown()
    {
        gameScene.GetInfoTileSelected((int)Mathf.Round(transform.position.x - 0.5f), (int)Mathf.Round(transform.position.z - 0.5f));
    }
}
