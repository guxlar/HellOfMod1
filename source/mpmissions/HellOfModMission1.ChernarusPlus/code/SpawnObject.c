//Spawn helper function
void SpawnObject( string type, vector position, vector orientation ) {
    auto obj = GetGame().CreateObject( type, position );
    obj.SetPosition( position );
    obj.SetOrientation( orientation );
    //Force collision update
    vector roll = obj.GetOrientation();
    roll [ 2 ] = roll [ 2 ] - 1;
    obj.SetOrientation( roll );
    roll [ 2 ] = roll [ 2 ] + 1;
    obj.SetOrientation( roll );
}