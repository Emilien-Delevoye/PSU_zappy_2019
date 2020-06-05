using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterGeneration : MonoBehaviour
{
    public GameObject character;
    public RuntimeAnimatorController runtimeAnimator;

    private Animator animator;

    private LinkedList<GameObject> characters;

    private Vector3 pos;
    private Quaternion rotation;

    // Start is called before the first frame update
    void Start()
    {
        characters = new LinkedList<GameObject>();
        animator = character.gameObject.GetComponent<Animator>();
        animator.runtimeAnimatorController = runtimeAnimator;
        pos = new Vector3(0f, 0f, 0f);
        rotation.x = 0;
        rotation.y = 10f;
        rotation.z = 0;
        character.transform.localScale = new Vector3(2.9f, 2.9f, 2.9f);
        for (int i = 0; i < 6 ; i++)
        {
            pos.x = Random.Range(0.5f, 5.5f);
            pos.z = Random.Range(0.5f, 5.5f);
            characters.AddLast(Instantiate(character, pos, rotation));
        }

    }

    // Update is called once per frame
    void Update()
    {
    }
}
