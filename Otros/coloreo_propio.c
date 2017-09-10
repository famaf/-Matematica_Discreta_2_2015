void coloreo_propio(GrafP G) {
    for (u32 i = 0; i < G->vertex_count; i++) {
        printf("Vertice: %u, Color: %u.\n", G->vertex_array[G->array_orden[i]]->id, G->vertex_array[G->array_orden[i]]->color);
        for (u32 j = 0; j < G->vertex_array[G->array_orden[i]]->grado; j++) {
            assert(G->vertex_array[G->array_orden[i]]->color == G->vertex_array[G->array_orden[i]]->vecinos[j]);
        }
    }
}
