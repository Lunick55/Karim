using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PongManager : MonoBehaviour
{
    public int MaxPlayers = 5;
    private List<Player> ActivePlayers;
    private GameObject PlayerPrefab;

    private Vector3 OriginOfPolygon = Vector3.zero;
    public float PolygonRadiusInVerticalScreenUnits = 0.9f;

    public void Start()
    {
        PlayerPrefab = Resources.Load<GameObject>("Prefab/Player");
        ActivePlayers = new List<Player>(MaxPlayers);
        InitPlayers();
        StartGame();
    }

    private void InitPlayers()
    {
        //Populate list of ActivePlayers based on players coming from lobby scene.
        ActivePlayers.Add(Instantiate(PlayerPrefab).GetComponent<Player>());
        ActivePlayers.Add(Instantiate(PlayerPrefab).GetComponent<Player>());
        ActivePlayers.Add(Instantiate(PlayerPrefab).GetComponent<Player>());
        ActivePlayers.Add(Instantiate(PlayerPrefab).GetComponent<Player>());
        ActivePlayers.Add(Instantiate(PlayerPrefab).GetComponent<Player>());
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            ActivePlayers.Add(Instantiate(PlayerPrefab).GetComponent<Player>());
            UpdateGoalPosts();
        }
        else if (Input.GetKeyDown(KeyCode.LeftShift) && ActivePlayers.Count > 2)
        {
            Destroy(ActivePlayers[0].gameObject);
            ActivePlayers.RemoveAt(0);
            UpdateGoalPosts();
        }
    }

    private void StartGame()
    {
        UpdateGoalPosts();
    }

    private void UpdateGoalPosts()
    {
        Vector3 WorldRadius = Vector3.right * Camera.main.orthographicSize * PolygonRadiusInVerticalScreenUnits;
        float PlayerThiccness = WorldRadius.x * 0.08f;
        float GoalThiccness = PlayerThiccness * 0.5f;

        //Special case because we can't create a closed shape.
        if (ActivePlayers.Count == 2)
        {
            float AnglePerGoal = 90.0f;
            for (int i = 0; i < ActivePlayers.Count; ++i)
            {
                Vector3 VecToRightGoal = WorldRadius;
                VecToRightGoal = Quaternion.AngleAxis(AnglePerGoal * i * 2, Vector3.forward) * VecToRightGoal;
                VecToRightGoal = Quaternion.AngleAxis(-AnglePerGoal * 0.5f, Vector3.forward) * VecToRightGoal;

                Vector3 VecToLeftGoal = WorldRadius;
                VecToLeftGoal = Quaternion.AngleAxis(AnglePerGoal * (i * 2 + 1), Vector3.forward) * VecToLeftGoal;
                VecToLeftGoal = Quaternion.AngleAxis(-AnglePerGoal * 0.5f, Vector3.forward) * VecToLeftGoal;

                Vector3 GoalRight = OriginOfPolygon + VecToRightGoal;
                Vector3 GoalLeft = OriginOfPolygon + VecToLeftGoal;

                Goal PlayerGoal = ActivePlayers[i].GetComponent<Goal>();
                PlayerGoal.SetGoalPosition(GoalLeft, GoalRight);
                PlayerGoal.SetGoalThickness(GoalThiccness);
            }
        }
        else
        {
            //based on amount of active players, create a polygon with that many sides.
            float AnglePerGoal = CalculateEqualAngle(ActivePlayers.Count);

            for (int i = 0; i < ActivePlayers.Count; ++i)
            {
                Vector3 VecToRightGoal = WorldRadius;
                VecToRightGoal = Quaternion.AngleAxis(AnglePerGoal * i, Vector3.forward) * VecToRightGoal;
                VecToRightGoal = Quaternion.AngleAxis(-AnglePerGoal * 0.5f, Vector3.forward) * VecToRightGoal;

                Vector3 VecToLeftGoal = WorldRadius;
                VecToLeftGoal = Quaternion.AngleAxis(AnglePerGoal * (i + 1), Vector3.forward) * VecToLeftGoal;
                VecToLeftGoal = Quaternion.AngleAxis(-AnglePerGoal * 0.5f, Vector3.forward) * VecToLeftGoal;

                Vector3 GoalRight = OriginOfPolygon + VecToRightGoal;
                Vector3 GoalLeft = OriginOfPolygon + VecToLeftGoal;

                Goal PlayerGoal = ActivePlayers[i].GetComponent<Goal>();
                PlayerGoal.SetGoalPosition(GoalLeft, GoalRight);
                PlayerGoal.SetGoalThickness(GoalThiccness);
            }
        }

        for (int i = 0; i < ActivePlayers.Count; ++i)
        {
            Goal PlayerGoal = ActivePlayers[i].GetComponent<Goal>();
            float GoalXSize = PlayerGoal.GetXScale();
            SpriteRenderer Renderer = ActivePlayers[i].GetComponent<SpriteRenderer>();
            Renderer.size = new Vector2(GoalXSize, PlayerThiccness);
            BoxCollider2D Collider = ActivePlayers[i].GetComponent<BoxCollider2D>();
            Collider.size = new Vector2(GoalXSize, PlayerThiccness);
        }
    }

    private float CalculateEqualAngle(int PlayerCount)
    {
        float Angle = 360.0f / PlayerCount;
        return Angle;
    }
}
