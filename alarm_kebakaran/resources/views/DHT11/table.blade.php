@extends('layout.template')
@section('title', 'Dashboard')


@section('content')

<h1> Data Sensor Dht11 </h1>
<table class="table table-striped table-hover table-responsive">
<thead>
    <tr>
      <th>No</th>
      <th>Suhu</th>
      <th>Kelembaban</th>
    </tr>
  </thead>
  <tbody>
  @foreach ($dhts as $key => $data)
    <tr>
        <td>{{ $dhts->firstItem() + $key }}</td>
        <td>{{ $data->suhu }} °C</td>
        <td>{{ $data->kelembaban }} %</td>
    </tr>
  @endforeach
  </tbody>
</table>
<div style="float: leftt;">
    Showing
    {{ $dhts->firstItem() }}
    to
    {{ $dhts->lastItem() }}
    of
    {{ $dhts->total() }}
    entries
</div>
<div style="float: right;">
    {{--  {{ $dhts->links() }}  --}}
    {{ $dhts->onEachSide(0)->links() }}
</div>

@endsection
