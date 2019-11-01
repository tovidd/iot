<?php

namespace App\Http\Controllers;

use App\SensorData;
use Illuminate\Http\Request;

class SensorDataController extends Controller
{
    public function index()
    {
        $data= SensorData::get();
        return response()->json($data, 200);
    }

    public function create()
    {
        //
    }

    public function store(Request $request)
    {
        $data= new SensorData;
        $data->humidity= (double) $_POST['humidity'];
        $data->temperature= (double) $_POST['temperature'];
        $data->distance= (double) $_POST['distance'];
        $succ= $data->save();
        if(!$succ)
        {
            return response()->json('Error saving', 500);
        }
        else
        {
            return response()->json('Success', 200);
        }
    }

    public function show($id)
    {
        $data= SensorData::find($id);
        if(is_null($data))
        {
            return response()->json('Not found', 404);
        }
        else
        {
            return response()->json($data, 200);
        }
    }

    public function edit(SensorData $sensorData)
    {
        //
    }

    public function update(Request $request, SensorData $sensorData)
    {
        //
    }

    public function destroy($id)
    {
        $data= SensorData::find($id);
        if(is_null($data))
        {
            return response()->json('Not found', 404);
        }

        $success= $data->delete(); 
        if(!$success)
        {
            return response()->json('Error deleting', 500);
        }
        else
        {
            return response()->json('Success deleting', 200);
        }
    }
}
