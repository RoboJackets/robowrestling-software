using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    public Rigidbody rb;
    public int rayDist = 100;

    /*
        Offset POSITION for lidar sensors
        centerOffset - lidars at 0 degree angle
        closeOffset - lidars at 5 degree angle
        outerOffset - lidars at 10 degree angle
    */
    public float centerOffset, outerOffset, closeOffset;

    /*
        Offset ANGLE for lidar sensors
        Note: center angle is not included because lidar is pointed straight forward

        closeAngle
        outerAngle
    */

    private float closeAngle = 5.0f;
    private float outerAngle = 10.0f;

    private Vector3 centerL, centerR, outerR, outerL, closeR, closeL;

    // Start is called before the first frame update
    void Start()
    {
        //initialize rigidbody of the object
        rb = GetComponent<Rigidbody>();
        
        
    }

    // Update is called once per frame
    void Update()
    {   
        //create vector3 positions for each sensor
        centerL = new Vector3(transform.position.x,transform.position.y, transform.position.z - centerOffset);
        centerR = new Vector3(transform.position.x,transform.position.y, transform.position.z + centerOffset);
        outerL = new Vector3(transform.position.x,transform.position.y, transform.position.z - outerOffset);
        outerR = new Vector3(transform.position.x,transform.position.y, transform.position.z + outerOffset);
        closeL = new Vector3(transform.position.x,transform.position.y, transform.position.z - closeOffset);
        closeR = new Vector3(transform.position.x,transform.position.y, transform.position.z + closeOffset);

        //create raycasts to represent the 6 lidar sensors
        Ray rayLCenter = new Ray(centerL , transform.forward);
        Ray rayRCenter = new Ray(centerR, transform.forward);;
        Ray rayROuter = new Ray(outerR, (Quaternion.AngleAxis(outerAngle, transform.up) * transform.forward));
        Ray rayLOuter = new Ray(outerL, (Quaternion.AngleAxis(-outerAngle, transform.up) * transform.forward));
        Ray rayLClose = new Ray(closeL, (Quaternion.AngleAxis(closeAngle, transform.up) * transform.forward));
        Ray rayRClose = new Ray(closeR, (Quaternion.AngleAxis(-closeAngle, transform.up) * transform.forward));

        //raycast hit info
        RaycastHit hit;
        Debug.DrawRay(centerL, transform.forward, Color.green);
        Debug.DrawRay(centerR, transform.forward, Color.green);
        Debug.DrawRay(outerL, (Quaternion.AngleAxis(-outerAngle, transform.up) * transform.forward), Color.green);
        Debug.DrawRay(outerR, (Quaternion.AngleAxis(outerAngle, transform.up) * transform.forward), Color.green);
        Debug.DrawRay(closeL, (Quaternion.AngleAxis(-closeAngle, transform.up) * transform.forward), Color.green);
        Debug.DrawRay(closeR, (Quaternion.AngleAxis(closeAngle, transform.up) * transform.forward), Color.green);

        
        //Check whether any lidar sensor is in contact with enemy
        Ray[] sensors = {rayLCenter, rayRCenter, rayROuter, rayLOuter, rayRClose, rayLClose};
        foreach (Ray lidar in sensors) {
            if(Physics.Raycast(lidar, out hit, rayDist)) {
            Debug.Log(hit.transform.gameObject);
            }
        }
    }
}
