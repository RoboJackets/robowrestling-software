using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    public RigidBody rb;
    // Start is called before the first frame update
    void Start()
    {
        rb.GetComponent<RigidBody>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
