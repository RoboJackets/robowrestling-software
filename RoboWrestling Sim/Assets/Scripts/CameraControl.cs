using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControl : MonoBehaviour
{
    //Keeps an array of all the cameras
    public GameObject[] cameras;
    private int cameraSize;
    private int index;

    void Start() 
    {
        //sets the main camera active and the rest off
        cameraSize = cameras.Length;
        index = 1;
        for (int i = 0; i < cameraSize; i++) {
            if (i != 0) {
                cameras[i].SetActive(false);
            } else {
                cameras[i].SetActive(true);
            }
            
        }
        Debug.Log(cameraSize);
    }

    // Update is called once per frame
    void Update()
    {
        //loops through the cameras when pressing tab key
       if(Input.GetKeyDown(KeyCode.Tab)) {
            Debug.Log(index);
            
            if(index == 0){
                cameras[2].SetActive(false);
                cameras[1].SetActive(false);
                cameras[index].SetActive(true);
                index++;
            }else if(index == 1){
                cameras[2].SetActive(false);
                cameras[0].SetActive(false);
                cameras[index].SetActive(true);
                index++;
            }else if(index == 2){
                cameras[1].SetActive(false);
                cameras[0].SetActive(false);
                cameras[index].SetActive(true);
                index = 0;
            }
        

       }
    }
}
