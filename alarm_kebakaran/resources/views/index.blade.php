@extends('layout.template')
@section('title', 'Dashboard')


@section('content')
<?php
    echo '<script language="javascript">';
    echo 'alert("Anda Berhasil Login")';
    echo '</script>';
?>
<div style="text-align: center">
    <img src="logo.png" class="rounded mx-auto d-block"  alt="User Image" style="width:300px;">
    <h1><b>MONITORING DAN KONTROL</b></h1>
    <H1><b>ALAT PENDETEKSI KEBAKARAN</b></H1>
    <br>
    <h2>ANGGI KISTANTO - 1711502763</h2>
    <br><br>
    <h6>2021@anggikistanto - monitoring dan kontrol alat pendeteksi kebakaran</h6>
</div>

@endsection
