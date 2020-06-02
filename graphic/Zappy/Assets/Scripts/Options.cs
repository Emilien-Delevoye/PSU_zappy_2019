using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;

public class Options : MonoBehaviour
{
    public AudioMixer audioMixer;
    public Slider mainVolumeSlider;

    private static float mainVolume;

    // Start is called before the first frame update
    void Start()
    {
        mainVolumeSlider.value = mainVolume;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetMainVolume(float volume)
    {
        audioMixer.SetFloat("Main Volume", volume);
        mainVolume = volume;
    }
}
