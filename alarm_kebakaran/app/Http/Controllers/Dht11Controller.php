<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use App\Models\Dht11Model;
use DateTime;
use DateTimeZone;

class Dht11Controller extends Controller
{
    // public function __construct()
    // {
    //     $this->Dht11Model = new Dht11Model();
    //     $this->middleware('auth');
    // }

    public function index()
    {
        return view('index');
    }

    public function dashboard()
    {
        return view('dashboard');
    }

    public function tabledht()
    {
        $data = Dht11Model::latest()->paginate(10);
        return view('DHT11.table', ['dhts'=>$data]);
    }

    public function insert(Request $request)
    {
        //cek array
        //dd($request->all());
        $timezone = "Asia/Jakarta";
        $date = new DateTime('now', new DateTimeZone($timezone));
        $tanggal = $date->format('Y-m-d');
        $localtime = $date->format('H:i:s');
        $timestamp = $date->format('Y-m-d H:i:s');

        $data = [
            'suhu' => $request->suhu,
            'kelembaban' => $request->kelembaban,
            'created_at' => $timestamp,


        ];
        DB::table('dht11')->insert($data);
        //AbsenModel::create($data);
        //return redirect()->route('masuk')->with('pesan', 'Sudah Absen Masuk');

    }
}
