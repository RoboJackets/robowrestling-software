using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    public Rigidbody rb;
    public int rayDist = 100;
    // Start is called before the first frame update
    void Start()
    {
        //initialize rigidbody of the object
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        //create raycast to represent lidar
        Ray ray = new Ray(this.transform.position, this.transform.forward);
        RaycastHit hit;
        if(Physics.Raycast(ray, out hit, rayDist)) {
            Debug.Log(hit.transform.gameObject);
        }
    }
}
