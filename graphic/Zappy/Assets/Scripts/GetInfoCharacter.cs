using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetInfoCharacter : MonoBehaviour
{
    private GameScene gameScene;

    private void Awake()
    {
        gameScene = GameObject.FindObjectOfType<GameScene>();
    }

    private void OnMouseDown()
    {
        Debug.Log("Player");
    }
}
