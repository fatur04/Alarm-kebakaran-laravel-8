<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use App\Models\Mq2Model;
use DateTime;
use DateTimeZone;

class Mq2Controller extends Controller
{
    public function tablemq2()
    {
        $data = Mq2Model::latest()->paginate(10);
        return view('mq2.tablemq', ['mqs'=>$data]);
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
            'gas' => $request->gas,
            'flame' => $request->flame,
            'created_at' => $timestamp,


        ];
        DB::table('mq2')->insert($data);
        //AbsenModel::create($data);
        //return redirect()->route('masuk')->with('pesan', 'Sudah Absen Masuk');

    }
}
